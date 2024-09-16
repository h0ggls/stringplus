#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *ans = S21_NULL;
  for (int i = (int)s21_strlen(str); i >= 0; i--) {
    if (str[i] == (char)c) {
      ans = (char *)str + i;
      break;
    }
  }

  return ans;
}