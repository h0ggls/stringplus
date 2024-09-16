#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  int null_flag = 1;
  char *ans;
  if (src != S21_NULL && str != S21_NULL) {
    ans = calloc(s21_strlen(src) + s21_strlen(str) + 1, sizeof(char *));
    s21_strncpy(ans, src, start_index);
    s21_strncat(ans, str, s21_strlen(str));
    s21_strncat(ans, src + start_index, s21_strlen(src + start_index));
    null_flag = 0;
  }
  return null_flag ? S21_NULL : ans;
}