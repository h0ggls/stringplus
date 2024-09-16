#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t len;
  char *ans = S21_NULL;
  if (needle[0] == '\0') {
    ans = (char *)haystack;
  } else {
    len = s21_strlen(needle);
    int count = 0;
    for (int i = 0; i < (int)s21_strlen(haystack); i++) {
      if (haystack[i] == needle[count]) {
        count++;
      } else {
        count = 0;
      }
      if (count == (int)len) {
        ans = (char *)haystack + i - count + 1;
        break;
      }
    }
  }
  return ans;
}