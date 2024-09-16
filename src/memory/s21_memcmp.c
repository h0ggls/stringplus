#include "../s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s21_str1, *s21_str2;
  int res = 0;
  s21_str1 = str1, s21_str2 = str2;
  for (; n-- > 0; s21_str1++, s21_str2++) {
    if (*s21_str1 != *s21_str2) {
      res = *s21_str1 < *s21_str2 ? -1 : 1;
      break;
    }
  }
  return res;
}  //| Сравнивает первые n байтов str1 и str2. |
