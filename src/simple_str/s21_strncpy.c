#include "../s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t count = 0;
  if (dest && src) {
    if (s21_strlen(dest) > s21_strlen(src)) {
      while (count < n && dest[count] != '\0') {
        dest[count] = src[count];
        count++;
      }
    } else {
      while (count < n && src[count] != '\0') {
        dest[count] = src[count];
        count++;
      }
    }
  }

  return dest;
}