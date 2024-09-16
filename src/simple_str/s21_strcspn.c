#include "../s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t ans = 0;
  for (int i = 0; i < (int)s21_strlen(str1); i++) {
    int false_flag = 0;
    for (int j = 0; j < (int)s21_strlen(str2); j++) {
      if (str1[i] == str2[j]) {
        false_flag = 1;
        break;
      }
    }
    if (false_flag) {
      break;
    } else {
      ans++;
    }
  }
  return ans;
}