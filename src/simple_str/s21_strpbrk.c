#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *ans = S21_NULL;
  for (int i = 0; i < (int)s21_strlen(str1); i++) {
    for (int j = 0; j < (int)s21_strlen(str2); j++) {
      if (str1[i] == str2[j]) {
        ans = (char *)(str1 + i);
        break;
      }
    }
    if (ans != S21_NULL) {
      break;
    }
  }
  return ans;
}