#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *byte = (unsigned char *)str;
  int match = 0;
  while (n-- > 0) {
    if (*byte == c) {
      match = 1;
      break;
    }
    byte++;
  }
  return (match) ? byte : S21_NULL;
}  //| Выполняет поиск первого вхождения символа c
   //(беззнаковый тип) в первых n байтах строки, на
   // которую указывает аргумент str. |
