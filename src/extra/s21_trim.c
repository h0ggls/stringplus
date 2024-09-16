#include "../s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *ans;
  int null_flag = 1;
  if (src != S21_NULL) {
    null_flag = 0;
    ans = calloc(s21_strlen(src), sizeof(src));
    s21_size_t src_len = s21_strlen(src);
    int i = 0;
    while (s21_strchr(trim_chars, src[i]) != S21_NULL) {
      i++;
    }

    s21_strncpy(ans, src + i, src_len - i);
    int j = src_len - 1;
    while (s21_strchr(trim_chars, src[j]) != S21_NULL) {
      j--;
    }

    ans[j - i + 1] = '\0';
  }
  return null_flag ? S21_NULL : ans;
}