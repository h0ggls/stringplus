#include "../s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *s21_str = (unsigned char *)str;
  if (str != S21_NULL) {
    for (s21_size_t i = 0; i < n; i++) {
      s21_str[i] = c;
    }
  }
  return s21_str;
}  //| Копирует символ c (беззнаковый тип) в первые n
   // символов строки, на которую указывает аргумент str. |
