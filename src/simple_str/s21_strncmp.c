#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int ans = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != '\0' || str2[i] != '\0') {
      if (!((int)str1[i] == (int)str2[i])) {
        ans = (int)str1[i] - (int)str2[i];
        break;
      }
    } else
      break;
  }
  return ans;
}