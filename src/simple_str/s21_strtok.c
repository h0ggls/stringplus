#include "../s21_string.h"

char *new_start = S21_NULL;

char *s21_strtok(char *str, const char *delim) {
  char *start = S21_NULL;
  int nun_flag = 1;
  if (delim != S21_NULL) {
    if (str == S21_NULL) {
      str = new_start;
    }

    for (int i = 0; i < (int)s21_strlen(str); i++) {
      if (s21_strchr(delim, (int)str[i]) == S21_NULL) {
        start = str + i;
        nun_flag = 0;
        break;
      }
    }

    if (!nun_flag) {
      for (int i = 0; i < (int)s21_strlen(start); i++) {
        if (s21_strchr(delim, (int)start[i]) != S21_NULL) {
          new_start = start + i + 1;
          start[i] = '\0';
          nun_flag = 0;
          break;
        } else {
          new_start = S21_NULL;
        }
      }
    } else {
      start = S21_NULL;
    }
  } else {
    start = S21_NULL;
  }

  return start;
}