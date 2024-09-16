#include "../s21_string.h"

void *s21_to_upper(const char *str) {
  int null_flag = 1;
  char *ans;
  if (str != S21_NULL && str[0] != '\0') {
    null_flag = 0;
    ans = calloc(s21_strlen(str), sizeof(char *));
    s21_strncpy(ans, str, s21_strlen(str));
    for (s21_size_t i = 0; i < s21_strlen(str); i++) {
      if ((int)ans[i] >= 97 && (int)ans[i] <= 122) {
        ans[i] = (char)((int)ans[i] - 32);
      }
    }
  } else if (str[0] == '\0') {
    ans = calloc(1, sizeof(char *));
    null_flag = 0;
    ans[0] = str[0];
  }
  return null_flag ? S21_NULL : ans;
}