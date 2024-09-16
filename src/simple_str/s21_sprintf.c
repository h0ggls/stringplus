#include "../s21_string.h"

char specifiers[] = "cdfsu%";
#define percent '%'

int s21_sprintf(char *str, const char *format, ...) {
  // изначальное положение str записываем в src чтобы узнать, сколько символов
  // мы записали
  char *start = str;

  va_list arguments;
  va_start(arguments, format);

  while (*format) {
    if (*format == percent) {
      // пропускаем % и переходим к флагам
      format++;
      Spec specs = {0};
      specs.number_system = 10;  // ставим по умолчанию
      format = set_specs(&specs, format);
      // Пропускаем лишние символы, пока не наткнёмся на буквенный спецификатор
      while (!s21_strrchr(specifiers, *format)) format++;
      str = parser(str, start, format, specs, &arguments);
    } else {
      // копируем символы из строки
      *str = *format;
      str++;
    }
    format++;
  }

  if (str != S21_NULL) {
    *str = '\0';
  }

  va_end(arguments);
  return (str - start);
}

/// @brief Обрабатывает флаги, ширину, точность, длину
/// @param specs
/// @param format
/// @param arguments
/// @return
const char *set_specs(Spec *specs, const char *format) {
  format = get_flags(format, specs);
  format = get_width(format, &specs->width);
  format = get_precision(format, specs);
  format = get_length(format, (int *)&specs->length);

  return format;
}

/// @brief проверяет наличие флагов между % и буквенным спецификатором
/// @param format
/// @param specs
/// @return
const char *get_flags(const char *format, Spec *specs) {
  int end_loop = 0;
  while (format) {
    switch (*format) {
      case '+':
        specs->plus = 1;
        break;
      case '-':
        specs->minus = 1;
        break;
      case ' ':
        specs->space = 1;
        break;
      case '0':
        specs->zero = 1;
        break;
      default:
        end_loop = 1;
        break;
    }
    if (end_loop) break;
    format++;
  }
  // Если есть флаг +, то пробел не ставится
  specs->space = (specs->space && !specs->plus);
  // Если выравнивание по правому краю, то нули не ставятся
  // specs->zero = (specs->zero && !specs->minus);
  return format;
}

/// @brief Записывает в ширину параметры
/// @param format const char *
/// @param width int *
/// @param arguments va_list *
/// @return const char *
const char *get_width(const char *format, int *width) {
  *width = 0;
  while (format) {
    if ('0' <= *format && *format <= '9') {
      *width *= 10;
      *width += *format - '0';
    } else {
      break;
    }
    format++;
  }
  return format;
}

/// @brief Записывает точность
/// @param format
/// @param specs
/// @return
const char *get_precision(const char *format, Spec *specs) {
  if (*format == '.') {
    specs->dot = 1;
    // specs->zero = 0;
    format++;
    format = get_width(format, &specs->accuracy);
  }
  return format;
}

/// @brief записываем длину
/// @param format
/// @param length
/// @return
const char *get_length(const char *format, int *length) {
  switch (*format) {
    case 'l':
      *length = 'l';
      format++;
      break;
    case 'h':
      *length = 'h';
      format++;
      break;
  }
  return format;
}

/// @brief Парсит данные и форматирует по флагам, ширине, точности, длине
/// @param str
/// @param src
/// @param format
/// @param specs
/// @param arguments
/// @return
char *parser(char *str, char *src, const char *format, Spec specs,
             va_list *arguments) {
  switch (*format) {
    // d и i отвечают за целочисленные числа, в sprintf одинаково работают
    case 'd':
    case 'i':
      str = print_decimal(str, specs, arguments);
      break;
    case 'u':
      str = print_u(str, specs, arguments);
      break;
    case 'c':
      int symbol = va_arg(*arguments, int);
      str = print_c(str, specs, symbol);
      break;
    case 's':
      str = print_s(str, specs, arguments);
      break;
    case 'f':
      str = print_double(str, specs, *(format - 1), arguments);
      break;
    case '%':
      str = print_c(str, specs, '%');
      break;
    default:
      str = S21_NULL;
      break;
  }
  if (!str) *src = '\0';
  return str;
}

char *print_decimal(char *str, Spec specs, va_list *arguments) {
  long int num = 0;
  switch (specs.length) {
    case 'l':
      num = (long)va_arg(*arguments, long int);
      break;
    case 'h':
      num = (long)va_arg(*arguments, int);
      break;
    default:
      num = (long)va_arg(*arguments, int);
      break;
  }
  s21_size_t size = get_size_to_decimal(&specs, num);
  char *buffer = malloc(sizeof(char) * size);
  if (buffer) {  // если удалось выделить место
    decimal_to_string(specs, num, buffer, size);
    for (s21_size_t i = 0; i < size; i++) {
      *str = buffer[i];
      str++;
    }
  }
  if (buffer) free(buffer);
  return str;
}

/// @brief функция подсчёта размера для buffer
/// @param specs
/// @param num
/// @return
s21_size_t get_size_to_decimal(Spec *specs, long int num) {
  s21_size_t size = 0;
  long int copy_num = num;
  if (copy_num < 0) copy_num = -copy_num;
  int num_len = decimal_len(copy_num);

  size += num_len;

  if ((s21_size_t)specs->width > size) size = specs->width;
  if ((s21_size_t)specs->accuracy > size) size = specs->accuracy;
  if (specs->space || specs->plus || num < 0) {
    specs->flag_to_size = 1;
    if ((s21_size_t)num_len >= size) {
      size++;
    }
  }

  return size;
}

/// @brief Записывает число в буффер
/// @param specs
/// @param num
/// @param str_to_num
/// @param size_to_decimal
/// @return
void decimal_to_string(Spec specs, long int num, char *buffer,
                       s21_size_t size) {
  // создаём массив, заполненный пробелами
  char str[size];
  s21_memset(str, ' ', size);  // s21

  // копируем число и делаем его положительным, чтобы его можно было потом
  // переписать
  long int copy_num = num;
  if (copy_num < 0) copy_num = -copy_num;

  int num_len = decimal_len(copy_num);
  int start_index_num, end_index_num;

  // Если есть минус, то к началу выравнивание, иначе к концу
  start_index_num = set_start_index_num(specs, num_len, size);
  end_index_num = start_index_num + num_len - 1;
  int flag_index = set_flag_index(specs, start_index_num);

  // заполняем нулями в начале, если есть такой флаг
  fill_with_zero(str, specs, start_index_num);

  // Обработка флагов +/-/пробел
  int num_type = 0;
  if (num > 0)
    num_type = 1;
  else if (num < 0)
    num_type = -1;

  add_flag_to_array(str, specs, flag_index, num_type, size);

  // записываем число
  unsigned_decimal_to_array(str, specs, copy_num, start_index_num,
                            end_index_num);

  // переносим число в буффер

  buffercpy(buffer, str, size);
}

void buffercpy(char *dest, char *src, s21_size_t size) {
  for (s21_size_t i = 0; i < size; i++) {
    dest[i] = src[i];
  }
}

int set_start_index_num(Spec specs, int num_len, s21_size_t size) {
  int start_index_num = size - num_len;
  if (specs.minus) {
    start_index_num = 0 + specs.flag_to_size;
  } else {
  }
  return start_index_num;
}

/// @brief высчитывает длину числа
/// @param num
/// @return
int decimal_len(long int num) {
  int len = 0;
  if (num == 0) len = 1;
  while (num > 0) {
    len++;
    num /= 10;
  }
  return len;
}

/// @brief выдаёт символ ascii у числа. Число должно быть от 0 до 15.
/// @param num
/// @param upper_case
/// @return
char num_to_char(int num, int upper_case) {
  // int ascii_difference = 32;  // буквы верхнего регистра находятся на 32
  // символа ниже
  int ascii_zero = '0';  // 48 == '0'
  // int ascii_letter_a = 'a';
  char ascii_number = '0';

  // if (10 <= num && num <= 15) {
  //   // получается число от 0 до 5, которое нужно прибавить к 'a', чтобы
  //   получить
  //   // нужную букву
  //   int letter_position = num - 10;
  //   ascii_number = (char)(letter_position + ascii_letter_a -
  //                         upper_case * ascii_difference);
  // }
  // чтобы получить номер символа ascii у числа, нужно к ascii нулю добавить
  // число
  if (0 <= num && num <= 9)
    ascii_number = (char)(num + ascii_zero + upper_case * 0);
  return ascii_number;
}

/// @brief обработка u
/// @param str
/// @param specs
/// @param format
/// @param arguments
/// @return
char *print_u(char *str, Spec specs, va_list *arguments) {
  unsigned long int num = 0;
  switch (specs.length) {
    case 'l':
      num = (unsigned long)va_arg(*arguments, unsigned long int);
      break;
    case 'h':
      num = (unsigned long)va_arg(*arguments, unsigned int);
      break;
    default:
      num = (unsigned int)va_arg(*arguments, unsigned int);
      break;
  }

  // функция для вычисления размера массива
  s21_size_t size_to_num =
      get_buf_size_unsigned_decimal(&specs, num);  // TODO()
  char *buffer = malloc(sizeof(char) * size_to_num);
  if (buffer) {
    unsigned_decimal_to_string(buffer, specs, num, size_to_num);
    // переписываем данные из буферного массива в массив {str}
    for (s21_size_t i = 0; i < size_to_num; i++) {
      *str = buffer[i];
      str++;
    }
  }
  if (buffer) free(buffer);
  return str;
}

s21_size_t get_buf_size_unsigned_decimal(Spec *specs, unsigned long int num) {
  s21_size_t result = 0;
  unsigned long int copy_num = num;
  while (copy_num > 0) {
    copy_num /= 10;
    result++;
  }
  if (copy_num == 0 && result == 0 && (specs->accuracy || specs->width)) {
    result++;
  }

  if ((s21_size_t)specs->width > result) result = specs->width;
  if ((s21_size_t)specs->accuracy > result) result = specs->accuracy;

  if (result == 0 && copy_num == 0 && !specs->accuracy && !specs->width &&
      !specs->space && !specs->dot) {
    result++;
  }
  return result;
}

void unsigned_decimal_to_string(char *buffer, Spec specs, unsigned long int num,
                                s21_size_t size) {
  // создаём массив, заполненный пробелами
  char str[size];
  s21_memset(str, ' ', size);

  int num_len = unsigned_decimal_len(num);
  int start_index_num, end_index_num;

  // Если есть минус, то к началу выравнивание, иначе к концу
  start_index_num = set_start_index_num(specs, num_len, size);
  end_index_num = start_index_num + num_len - 1;

  // заполняем нулями в начале, если есть такой флаг
  fill_with_zero(str, specs, start_index_num);

  // записываем число
  unsigned_decimal_to_array(str, specs, num, start_index_num, end_index_num);

  // переносим число в буффер
  buffercpy(buffer, str, size);
}

void fill_with_zero(char *array, Spec specs, int start_index_num) {
  if (specs.zero || specs.accuracy) {
    int start_index_for_zero = 0;
    // corner case: "%9.5d", 123 -> "    00123"
    if (specs.width && specs.accuracy && specs.width > specs.accuracy) {
      start_index_for_zero = specs.width - specs.accuracy;
    }
    for (int i = start_index_for_zero; i < start_index_num; i++) {
      array[i] = '0';
    }
  }
}

/// @brief высчитывает длину числа
/// @param num
/// @return
int unsigned_decimal_len(unsigned long int num) {
  int len = 0;
  if (num == 0) len = 1;
  while (num > 0) {
    len++;
    num /= 10;
  }
  return len;
}

char *print_c(char *str, Spec specs, int symbol) {
  char *ptr = S21_NULL;
  int i = 0;
  while (specs.width - 1 > 0 && !specs.minus) {
    *str = ' ';
    str++;
    i++;
    specs.width--;
  }
  if (symbol <= 127) {
    *str = symbol;
    str++;
    i++;
    while (specs.width - 1 > 0 && specs.minus) {
      *str = ' ';
      str++;
      i++;
      specs.width--;
    }
    ptr = str;
  }
  return ptr;
}

char *print_s(char *str, Spec specs, va_list *arguments) {
  char *ptr = str;
  char *string = va_arg(*arguments, char *);

  // если удалось получить строку
  if (string) {
    // int tmp = specs.width;
    int i = 0;
    // если ширина указана или если ширина меньше длины строки
    if ((s21_size_t)specs.width < s21_strlen(string))
      specs.width = s21_strlen(string);

    // если ширина больше чем длина строки, то пустое место заполняем пробелами
    // blank = кол-ву пробелов
    int blank = specs.width - s21_strlen(string);

    // если точность не указана
    if (specs.accuracy == 0) specs.accuracy = specs.width;

    // если точность меньше изначальной ширины и она указана
    // меняем кол-во пробелов
    // if (specs.accuracy != 0 && specs.accuracy < tmp) {
    //   blank = tmp - specs.accuracy;
    // }

    // заполняем пробелы слева (если нет флага -)
    while (blank && !specs.minus) {
      *str = ' ';
      str++;
      blank--;
    }

    // посимвольно записываем из полученной строки {string} в {str}
    while (*string != '\0') {
      if (!specs.accuracy) break;
      *str = *string;
      str++;
      string++;
      i++;
      specs.accuracy--;
    }

    // если был указан флаг - тогда заполняем пробелы справа
    while (blank && specs.minus) {
      *str = ' ';
      str++;
      blank--;
    }
  } else {
    // если нам не удалось получить строку из параметра, пишем в нашу строку
    // (null)
    str = s21_memcpy(str, "(null)", 6);  // s21
    str += 6;
  }

  // присваиваем ptr str и возвращаем его, чтобы передвинуть указатель нашей
  // строки
  if (ptr) ptr = str;
  return ptr;
}

// %7Lf 12344.456
char *print_double(char *str, Spec specs, char format, va_list *arguments) {
  double num = 0;
  if (format == 'L') {
    num = va_arg(*arguments, long double);
  } else {
    num = va_arg(*arguments, double);
  }
  // вычисляем размер (учитываем наличие точки)
  s21_size_t size = get_size_to_double(&specs, num);
  char *buffer = malloc(sizeof(char) * size);

  if (buffer) {
    double_to_string(buffer, specs, num, size);

    for (s21_size_t i = 0; i < size; i++) {
      *str = buffer[i];
      str++;
    }
  }
  if (buffer) free(buffer);
  return str;
}

s21_size_t get_size_to_double(Spec *specs, long double num) {
  s21_size_t size = 0;
  long double copy_num = num;
  if (copy_num < 0) copy_num = -copy_num;

  // разбиваем число на целую и дробную часть
  // 1234.5678 =>
  // integer = 1234
  // frac = 0.5678
  long double integer = 0;
  modfl(copy_num, &integer);

  int integer_len = unsigned_decimal_len((unsigned long)integer);
  size += (s21_size_t)integer_len;

  // по умолчанию, если не дана точность, используется точность 6
  // format: %f input: 1.123456789 output:1.123457:
  s21_size_t accuracy = (s21_size_t)set_accuracy_for_double(specs);
  s21_size_t dot_len = (s21_size_t)set_dot_len(specs);

  size += accuracy;
  size += dot_len;
  int num_len = (int)size;

  if ((s21_size_t)specs->width > size) size = specs->width;

  if (specs->space || specs->plus || num < 0) {
    specs->flag_to_size = 1;
    if (num_len >= (int)size) {
      size++;
    }
  }

  return size;
}

void double_to_string(char *buffer, Spec specs, long double num,
                      s21_size_t size) {
  // создаём массив, заполненный пробелами
  char str[size];
  s21_memset(str, ' ', size);

  // по умолчанию, если не дана точность, используется точность 6
  // format: %f input: 1.123456789 output:1.123457:
  int accuracy = set_accuracy_for_double(&specs);

  long double copy_num = num;
  if (copy_num < 0) {
    copy_num = -copy_num;
  }
  // разбиваем число на целую и дробную часть
  // 1234.5678 =>
  // integer = 1234
  // int_fraction = 5678 (колво чисел зависит от точности)
  long double integer = 0;
  modfl(copy_num, &integer);
  int int_fraction = fractional_part_as_int(copy_num, accuracy);
  int integer_len = unsigned_decimal_len((unsigned long)integer);

  // общая длина числа состоит из длины целой части, точки и точности
  int dot_len = set_dot_len(&specs);
  int num_len = integer_len + dot_len + accuracy;
  int start_index_num, end_index_num, end_index_int_num, index_dot;
  // Если есть минус, то к началу выравнивание, иначе к концу
  start_index_num = set_start_index_num(specs, num_len, size);
  end_index_num = start_index_num + num_len - 1;
  index_dot = start_index_num + integer_len;
  end_index_int_num = start_index_num + integer_len - 1;
  int flag_index = start_index_num - 1;
  if (specs.zero) {  // если добавляли нули, то в начале флаг ставится
    flag_index = 0;
  }
  // заполняем нулями в начале, если есть такой флаг
  if (specs.zero) {
    s21_memset(str, '0', start_index_num);
  }
  // Обработка флагов +/-/пробел

  int num_type = 0;  // определяет знак числа или если оно равно 0
  if (num > 0)
    num_type = 1;
  else if (num < 0)
    num_type = -1;
  add_flag_to_array(str, specs, flag_index, num_type, size);

  // записываем целую часть
  // начинаем запись с конца т.к. запись 12345 начинается с '5'
  unsigned_decimal_to_array(str, specs, (unsigned long)integer, start_index_num,
                            end_index_int_num);
  // записываем точку и точность
  if (specs.dot) {
    // если точность не нулевая, значит пишем точку и точность
    if (specs.accuracy) {
      str[index_dot] = '.';
    }
    unsigned_decimal_to_array(str, specs, (unsigned long)int_fraction,
                              index_dot + 1, end_index_num);
  } else {
    str[index_dot] = '.';
    unsigned_decimal_to_array(str, specs, (unsigned long)int_fraction,
                              index_dot + 1, end_index_num);
  }
  // переносим число в буффер
  buffercpy(buffer, str, size);
}

int set_dot_len(Spec *specs) {
  int dot = 1;
  if (specs->accuracy == 0) {
    if (specs->dot) {
      dot = 0;
    }
  }
  return dot;
}

int set_accuracy_for_double(Spec *specs) {
  int accuracy = specs->accuracy;
  if (specs->accuracy == 0) {
    if (!specs->dot) {
      accuracy = 6;
    }
  }
  return accuracy;
}

int set_flag_index(Spec specs, int start_index_num) {
  int flag_index = start_index_num - 1;
  if (specs.zero) {  // если добавляли нули, то в начале флаг ставится
    flag_index = 0;
  }
  // corner case: "%+9.5d", 123 -> "   +00123"
  if (specs.width && specs.accuracy && specs.width > specs.accuracy) {
    flag_index = specs.width - specs.accuracy - 1;
  }
  return flag_index;
}

void add_flag_to_array(char *array, Spec specs, int flag_index, int num_type,
                       s21_size_t size) {
  if (specs.space && num_type >= 0 && size) {
    array[flag_index] = ' ';
  }
  if (num_type < 0 && size) {
    array[flag_index] = '-';
  }
  if (num_type > 0 && specs.plus && size) {
    array[flag_index] = '+';
  }
}

int fractional_part_as_int(long double number, int number_of_decimal_places) {
  long double dummy;
  long double frac = modfl(number, &dummy);
  return round(frac * pow(10, number_of_decimal_places));
}

/// @brief Переписывает часть неотрицательного числа в char массив.
/// @param array
/// @param specs
/// @param num
/// @param start_index
/// @param end_index
void unsigned_decimal_to_array(char *array, Spec specs, unsigned long int num,
                               int start_index, int end_index) {
  for (int i = end_index; i >= start_index; i--) {
    char sym = num_to_char((long)num % specs.number_system, specs.upper_case);
    array[i] = sym;
    num /= specs.number_system;
  }
}