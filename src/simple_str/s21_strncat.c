#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t start_length = s21_strlen(dest);
  if (s21_strlen(src) < n) n = s21_strlen(src);

  for (s21_size_t i = 0; i < n; i++) {
    dest[start_length + i] = src[i];
  }

  return dest;
}