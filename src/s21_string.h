#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef long long unsigned s21_size_t;

#define S21_NULL (void *)0

char *s21_strncpy(char *dest, const char *src, s21_size_t n);
// 8 работает нормально

s21_size_t s21_strcspn(const char *str1, const char *str2);
// 9 //работает хорошо, максимум это добавить чтобы была проверка на конец
// строки

char *s21_strerror(int errnum);  // 10 работает, но нужно тестить на маках, и
                                 // узнать можно ли вообще использовать глобалки

s21_size_t s21_strlen(const char *str);  // 11  //сделанно

char *s21_strpbrk(const char *str1, const char *str2);  // 12 //работает

char *s21_strrchr(const char *str, int c);  // 13 //работает

char *s21_strstr(const char *haystack, const char *needle);  // 14//работает

char *s21_strtok(char *str, const char *delim);  // 15

// 5 //работает
char *s21_strncat(char *dest, const char *src, s21_size_t n);

// 6 //работает
char *s21_strchr(const char *str, int c);

// 7 //
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

// extra 1
void *s21_to_upper(const char *str);

// extra 2
void *s21_to_lower(const char *str);

// extra 3
void *s21_insert(const char *src, const char *str, s21_size_t start_index);

// extra 4
void *s21_trim(const char *src, const char *trim_chars);

// mem* funcs
void *s21_memchr(const void *str, int c, s21_size_t n);

int s21_memcmp(const void *str1, const void *str2, s21_size_t n);

void *s21_memcpy(void *dest, const void *src, s21_size_t n);

void *s21_memset(void *str, int c, s21_size_t n);

/// @brief Spec от Specifiers (спецификаторы). Так же сюда входят флаги
typedef struct {
  // Выравнивание по левому краю в пределах заданной ширины поля.
  int minus;
  // Заставляет явно указывать знак плюс или минус (+ или -) даже для
  // положительных чисел
  int plus;
  // Если знак не будет выведен, перед значением вставляется пробел.
  int space;
  // вывод 16 и 8 ричных чисел в формате 0х и 0 соответсвенно
  int zero;
  // Минимальное количество печатаемых символов. Если выводимое значение короче
  // этого числа, результат дополняется пробелами.
  int width;
  // точность
  int accuracy;
  // тип переменной (%1f Lf Ld and etc.)
  char length;
  // система исчисления
  int number_system;
  // если число отрицательное или есть + или space
  int flag_to_size;
  // наличие точки (говорит о наличии точности в числе)
  int dot;
  // если спецификатор - буква в верхнем регистре (G E F X)
  int upper_case;
} Spec;

int s21_sprintf(char *str, const char *format, ...);

// sprintf functions

const char *set_specs(Spec *specs, const char *format);

const char *get_flags(const char *format, Spec *specs);

const char *get_width(const char *format, int *width);

const char *get_precision(const char *format, Spec *specs);

const char *get_length(const char *format, int *length);

char *parser(char *str, char *src, const char *format, Spec specs,
             va_list *arguments);

char *print_decimal(char *str, Spec specs, va_list *arguments);

s21_size_t get_size_to_decimal(Spec *specs, long int num);

void decimal_to_string(Spec specs, long int num, char *buffer, s21_size_t size);

void buffercpy(char *dest, char *src, s21_size_t size);

int set_start_index_num(Spec specs, int num_len, s21_size_t size);

int decimal_len(long int num);

char num_to_char(int num, int upper_case);

char *print_u(char *str, Spec specs, va_list *arguments);

s21_size_t get_buf_size_unsigned_decimal(Spec *specs, unsigned long int num);

void unsigned_decimal_to_string(char *buffer, Spec specs, unsigned long int num,
                                s21_size_t size);

void fill_with_zero(char *array, Spec specs, int start_index_num);

int unsigned_decimal_len(unsigned long int num);

char *print_c(char *str, Spec specs, int symbol);

char *print_s(char *str, Spec specs, va_list *arguments);

char *print_double(char *str, Spec specs, char format, va_list *arguments);

s21_size_t get_size_to_double(Spec *specs, long double num);

void double_to_string(char *buffer, Spec specs, long double num,
                      s21_size_t size);

int set_dot_len(Spec *specs);

int set_accuracy_for_double(Spec *specs);

int set_flag_index(Spec specs, int start_index_num);

void add_flag_to_array(char *array, Spec specs, int flag_index, int num_type,
                       s21_size_t size);

int fractional_part_as_int(long double number, int number_of_decimal_places);

void unsigned_decimal_to_array(char *array, Spec specs, unsigned long int num,
                               int start_index, int end_index);
