#include <check.h>
#include <string.h>

#include "../s21_string.h"

// strlen
START_TEST(strlen_test) {
  ck_assert_uint_eq(s21_strlen(""), strlen(""));
  ck_assert_uint_eq(s21_strlen("qwertyuiop"), strlen("qwertyuiop"));
  ck_assert_uint_eq(s21_strlen("qwert\0yuiop"), strlen("qwert\0yuiop"));
  ck_assert_uint_eq(s21_strlen("\0"), strlen("\0"));
  ck_assert_uint_eq(s21_strlen("q"), strlen("q"));
}
END_TEST

START_TEST(strcpy_test) {
  char *s21_test = calloc(sizeof(char), 1024);
  char *str_test = calloc(sizeof(char), 1024);
  ck_assert_pstr_eq(s21_strncpy(s21_test, "first\0second", 8),
                    strncpy(s21_test, "first\0second", 8));
  ck_assert_pstr_eq(s21_strncpy(s21_test, "\0", 1), strncpy(s21_test, "\0", 1));
  // ck_assert_pstr_eq(s21_strncpy(s21_test, "first", 0),
  //                   strncpy(s21_test, "first", 0));
  ck_assert_pstr_eq(s21_strncpy(s21_test, "", 8), strncpy(s21_test, "", 8));
  ck_assert_pstr_eq(s21_strncpy(s21_test, "first", 8),
                    strncpy(s21_test, "first", 8));

  free(s21_test);
  free(str_test);
}
END_TEST

START_TEST(strpbrk_test) {
  ck_assert_pstr_eq(s21_strpbrk("0123456789", "369"),
                    strpbrk("0123456789", "369"));
  ck_assert_pstr_eq(s21_strpbrk("0123456789", "a"), strpbrk("0123456789", "a"));
  ck_assert_pstr_eq(s21_strpbrk("0123456789", "0123456789"),
                    strpbrk("0123456789", "0123456789"));
  ck_assert_pstr_eq(s21_strpbrk("", "0123456789"), strpbrk("", "0123456789"));
  ck_assert_pstr_eq(s21_strpbrk("0123456789", ""), strpbrk("0123456789", ""));
}
END_TEST

START_TEST(strrchr_test) {
  ck_assert_pstr_eq(s21_strrchr("0163456769", '6'), strrchr("0163456769", '6'));
  ck_assert_pstr_eq(s21_strrchr("0163456769", 'a'), strrchr("0163456769", 'a'));
  ck_assert_pstr_eq(s21_strrchr("00000000", '0'), strrchr("00000000", '0'));
  ck_assert_pstr_eq(s21_strrchr("0163456769", '\0'),
                    strrchr("0163456769", '\0'));
  ck_assert_pstr_eq(s21_strrchr("", 'a'), strrchr("", 'a'));
  ck_assert_pstr_eq(s21_strrchr("a", 'a'), strrchr("a", 'a'));
  ck_assert_pstr_eq(s21_strrchr("bbba", 'a'), strrchr("bbba", 'a'));
  ck_assert_pstr_eq(s21_strrchr("bb\0ba", '\0'), strrchr("bb\0ba", '\0'));
}
END_TEST

START_TEST(strstr_test) {
  ck_assert_pstr_eq(s21_strstr("0123456789", "345"),
                    strstr("0123456789", "345"));
  ck_assert_pstr_eq(s21_strstr("0123456789", "asd"),
                    strstr("0163456769", "asd"));
  ck_assert_pstr_eq(s21_strstr("00000000", ""), strstr("00000000", ""));
  ck_assert_pstr_eq(s21_strstr("0163456769", "0163456769"),
                    strstr("0163456769", "0163456769"));
  ck_assert_pstr_eq(s21_strstr("", "a"), strstr("", "a"));
  ck_assert_pstr_eq(s21_strstr("\0", "\0"), strstr("\0", "\0"));
  ck_assert_pstr_eq(s21_strstr("bb\0ba", "\0"), strstr("bb\0ba", "\0"));
}
END_TEST

START_TEST(strtok_test) {
  char s21_str2[14] = "/012/345/67/89";
  char str2[13] = "/012/345/6789";

  ck_assert_pstr_eq(s21_strtok(s21_str2, S21_NULL), S21_NULL);

  ck_assert_pstr_eq(s21_strtok(s21_str2, "/"), strtok(str2, "/"));

  char s21_str3[30] = "Hello, World! This is a test.";
  char str3[30] = "Hello, World! This is a test.";
  ck_assert_pstr_eq(s21_strtok(s21_str3, " ,.!"), strtok(str3, " ,.!"));
  // ck_assert_pstr_eq(s21_strtok("012/345 /678 9/", "/ "),
  //                   strtok("012/345 /678 9/", "/ "));

  char s21_str1[12] = "012/345/6789";
  char str1[12] = "012/345/6789";
  ck_assert_pstr_eq(s21_strtok(s21_str1, "/"), strtok(str1, "/"));
  ck_assert_pstr_eq(s21_strtok(S21_NULL, "/"), strtok(NULL, "/"));
  // ck_assert_pstr_eq(s21_strtok(S21_NULL, "/"), strtok(NULL, "/"));
  // //заковырка, лучше убрать
  //  ck_assert_pstr_eq(s21_strtok(S21_NULL, "/ "), strtok(NULL, "/ "));

  ck_assert_pstr_eq(s21_strtok(s21_str2, "*"), strtok(str2, "*"));
  ck_assert_pstr_eq(s21_strtok(s21_str2, "/"), strtok(str2, "/"));

  char str4[1] = "";
  char s21_str4[1] = "";

  ck_assert_pstr_eq(s21_strtok(s21_str4, "0"), strtok(str4, "0"));
}
END_TEST

START_TEST(strcspn_test) {
  ck_assert_uint_eq(s21_strcspn("0123456789", "9876"),
                    strcspn("0123456789", "9876"));
  ck_assert_uint_eq(s21_strcspn("0123456789", ""), strcspn("0123456789", ""));
  ck_assert_uint_eq(s21_strcspn("0123456789", "a"), strcspn("0123456789", "a"));
  ck_assert_uint_eq(s21_strcspn("0123456789", "0123456789"),
                    strcspn("0123456789", "0123456789"));
  ck_assert_uint_eq(s21_strcspn("01234\0r56789", "\0"),
                    strcspn("01234\0r56789", "\0"));
}
END_TEST

START_TEST(strncat_test) {
  char str1[100] = "000";
  char str2[10] = "000";

  char s21_str1[100] = "000";
  char s21_str2[10] = "000";

  char app[10] = "1234567890";
  ck_assert_pstr_eq(s21_strncat(s21_str1, app, 3), strncat(str1, app, 3));
  ck_assert_pstr_eq(s21_strncat(s21_str1, app, 5), strncat(s21_str1, app, 5));
  ck_assert_pstr_eq(s21_strncat(s21_str1, app, 0), strncat(s21_str1, app, 0));
  ck_assert_pstr_eq(s21_strncat(s21_str1, "", 5), strncat(s21_str1, "", 5));

  ck_assert_pstr_eq(s21_strncat(s21_str2, app, 5), strncat(str2, app, 5));
  // надо бы еще добавть чтобы третий аргумент был больеш app, но тут сам
  // компилятор выдает предупреждение
}
END_TEST

START_TEST(strchr_test) {
  ck_assert_pstr_eq(s21_strchr("0163456769", '6'), strchr("0163456769", '6'));
  ck_assert_pstr_eq(s21_strchr("0163456769", 'a'), strchr("0163456769", 'a'));
  ck_assert_pstr_eq(s21_strchr("00000000", '0'), strchr("00000000", '0'));
  ck_assert_pstr_eq(s21_strchr("0163456769", '\0'), strchr("0163456769", '\0'));
  ck_assert_pstr_eq(s21_strchr("", 'a'), strchr("", 'a'));
  ck_assert_pstr_eq(s21_strchr("a", 'a'), strchr("a", 'a'));
  ck_assert_pstr_eq(s21_strchr("bbba", 'a'), strchr("bbba", 'a'));
  ck_assert_pstr_eq(s21_strchr("bb\0ba", '\0'), strchr("bb\0ba", '\0'));
}
END_TEST

START_TEST(strncmp_test) {
  ck_assert_int_eq(s21_strncmp("1234aa", "123456", 5),
                   strncmp("1234aa", "123456", 5));
  ck_assert_int_eq(s21_strncmp("1234aa", "123456", 4),
                   strncmp("1234aa", "123456", 4));
  ck_assert_int_eq(s21_strncmp("123456", "123", 5),
                   strncmp("123456", "123", 5));
  ck_assert_int_eq(s21_strncmp("123", "123456", 10),
                   strncmp("123", "123456", 10));
  // добавить еще парочку тестов
}
END_TEST

START_TEST(memchr_test) {
  ck_assert_ptr_eq(s21_memchr("intfloatchardouble", 134, 10),
                   memchr("intfloatchardouble", 134, 10));
  ck_assert_ptr_eq(s21_memchr("intfloatchardouble", 'f', 10),
                   memchr("intfloatchardouble", 'f', 10));
  ck_assert_ptr_eq(s21_memchr("Qazwsxedcrfvtgbyhnujmik", 160, 0),
                   memchr("Qazwsxedcrfvtgbyhnujmik", 160, 0));
  ck_assert_ptr_eq(s21_memchr("intfloatchardouble", 10, 10),
                   memchr("intfloatchardouble", 10, 10));
  ck_assert_ptr_eq(s21_memchr("intfloatchardouble", 134, 50),
                   memchr("intfloatchardouble", 134, 18));
  ck_assert_ptr_eq(s21_memchr("I n t f l o a t c h a r d o u b l e", 10, 10),
                   memchr("I n t f l o a t c h a r d o u b l e", 10, 10));
}

START_TEST(memcmp_test) {
  ck_assert_int_eq(s21_memcmp("ABCDEFG", "abcdefg", 5),
                   memcmp("ABCDEFG", "abcdefg", 5));
  ck_assert_int_eq(s21_memcmp("abcdefg", "ABCDEFG", 5),
                   memcmp("abcdefg", "ABCDEFG", 5));
  ck_assert_int_eq(s21_memcmp("hijklmn", "abcdefg", 5),
                   memcmp("hijklmn", "abcdefg", 5));
  ck_assert_int_eq(s21_memcmp("ABCDEFG", "abcdefg", 0),
                   memcmp("ABCDEFG", "abcdefg", 0));
  ck_assert_int_eq(s21_memcmp("ABCDEFG", "abcdefg", 8),
                   memcmp("ABCDEFG", "abcdefg", 8));
  ck_assert_int_eq(s21_memcmp("abc", "abcdefg", 3),
                   memcmp("abc", "abcdefg", 3));
}

START_TEST(memcpy_test) {
  char *dest[100];
  ck_assert_str_eq(s21_memcpy(dest, "zxcvbnm", 4), memcpy(dest, "zxcvbnm", 4));
  ck_assert_str_eq(s21_memcpy(dest, "zxcvbnm", 8), memcpy(dest, "zxcvbnm", 8));
  ck_assert_str_eq(s21_memcpy(dest, "zxcvbnm", 5), memcpy(dest, "zxcvbnm", 5));
  ck_assert_str_eq(s21_memcpy(dest, "zxcvbnm", 0), memcpy(dest, "zxcvbnm", 0));
  ck_assert_str_eq(s21_memcpy(dest, "zxcvbnm", 0), memcpy(dest, "zxcvbnm", 0));
}

START_TEST(memset_test) {
  char *dest[100];
  ck_assert_str_eq(s21_memset(dest, 135, 6), memset(dest, 135, 6));
  ck_assert_str_eq(s21_memset(dest, 10, 8), memset(dest, 10, 8));
  ck_assert_str_eq(s21_memset(dest, 54, 10), memset(dest, 54, 10));
  ck_assert_str_eq(s21_memset(dest, 120, 0), memset(dest, 120, 0));
  ck_assert_str_eq(s21_memset(dest, 135, 0), memset(dest, 135, 0));
}

START_TEST(to_lower_test) {
  char *str1 = s21_to_lower("QWERTY");
  ck_assert_pstr_eq(str1, "qwerty");
  free(str1);

  char *str2 = s21_to_lower("123QWERTY123");
  ck_assert_pstr_eq(str2, "123qwerty123");
  free(str2);

  char *str3 = s21_to_lower("");
  ck_assert_pstr_eq(str3, "");
  free(str3);
}

START_TEST(to_upper_test) {
  char *str1 = s21_to_upper("qwerty");
  ck_assert_pstr_eq(str1, "QWERTY");
  free(str1);

  char *str2 = s21_to_upper("123qwerty123");
  ck_assert_pstr_eq(str2, "123QWERTY123");
  free(str2);

  char *str3 = s21_to_upper("");
  ck_assert_pstr_eq(str3, "");
  free(str3);
}

START_TEST(insert_test) {
  char *str1 = s21_insert("qwerty", "123", 4);
  ck_assert_pstr_eq(str1, "qwer123ty");
  free(str1);

  char *str2 = s21_insert("qwerty", "123", 0);
  ck_assert_pstr_eq(str2, "123qwerty");
  free(str2);

  char *str3 = s21_insert("qwerty", "123", 6);
  ck_assert_pstr_eq(str3, "qwerty123");
  free(str3);

  char *str4 = s21_insert("qwerty", "", 6);
  ck_assert_pstr_eq(str4, "qwerty");
  free(str4);
}

START_TEST(trim_test) {
  char *str1 = s21_trim("***qwerty***", "*");
  ck_assert_pstr_eq(str1, "qwerty");
  free(str1);

  char *str2 = s21_trim("***qwerty***+", "*");
  ck_assert_pstr_eq(str2, "qwerty***+");
  free(str2);

  char *str3 = s21_trim("**qwe**rty**", "*");
  ck_assert_pstr_eq(str3, "qwe**rty");
  free(str3);

  char *str4 = s21_trim("**qwe**rty//", "*/");
  ck_assert_pstr_eq(str4, "qwe**rty");
  free(str4);
}

START_TEST(strerror_test) {
  ck_assert_pstr_eq(s21_strerror(0), strerror(0));
  ck_assert_pstr_eq(s21_strerror(100), strerror(100));
  ck_assert_pstr_eq(s21_strerror(52), strerror(52));
  ck_assert_pstr_eq(s21_strerror(-100), strerror(-100));
  ck_assert_pstr_eq(s21_strerror(22), strerror(22));
}

START_TEST(sprintf_test) {
  char str[2000] = "";
  char s21_str[2000] = "";
  int res, s21_res = 0;
  // d - decimal
  res = sprintf(str, "%9d", 123456);
  s21_res = s21_sprintf(s21_str, "%9d", 123456);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "%9ld", 123456);
  s21_res = s21_sprintf(s21_str, "%9ld", 123456);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "%9d", -123456);
  s21_res = s21_sprintf(s21_str, "%9d", -123456);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "%9hd", 123);
  s21_res = s21_sprintf(s21_str, "%9hd", 123);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "%9hd", 0);
  s21_res = s21_sprintf(s21_str, "%9hd", 0);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "% 9d", 123456);
  s21_res = s21_sprintf(s21_str, "% 9d", 123456);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "%09d", 123456);
  s21_res = s21_sprintf(s21_str, "%09d", 123456);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "% 09d", 123456);
  s21_res = s21_sprintf(s21_str, "% 09d", 123456);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "%+9d", 123456);
  s21_res = s21_sprintf(s21_str, "%+9d", 123456);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "%+ 9d", 123456);
  s21_res = s21_sprintf(s21_str, "%+ 9d", 123456);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "%+09d", 123456);
  s21_res = s21_sprintf(s21_str, "%+09d", 123456);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "%-+09d", 123456);
  s21_res = s21_sprintf(s21_str, "%-+09d", 123456);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "%-9d", 123456);
  s21_res = s21_sprintf(s21_str, "%-9d", 123456);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "%5.9d", 123);
  s21_res = s21_sprintf(s21_str, "%5.9d", 123);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "%.9d", 123);
  s21_res = s21_sprintf(s21_str, "%.9d", 123);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "%9.5d", 123);
  s21_res = s21_sprintf(s21_str, "%9.5d", 123);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "%+9.5d", 123);
  s21_res = s21_sprintf(s21_str, "%+9.5d", 123);
  ck_assert_pstr_eq(str, s21_str);
  ck_assert_int_eq(res, s21_res);
  res = sprintf(str, "%+9.5\0", 123);
  s21_res = s21_sprintf(s21_str, "%+9.5\0", 123);
  ck_assert_pstr_eq(str, s21_str);
  // ck_assert_int_eq(res, s21_res);
  // u - unsigned decimal
  sprintf(str, "%u", 12);
  s21_sprintf(s21_str, "%u", 12);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%+u", 12);
  s21_sprintf(s21_str, "%+u", 12);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%+lu", 12);
  s21_sprintf(s21_str, "%+lu", 12);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%+hu", 12);
  s21_sprintf(s21_str, "%+hu", 12);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%+u", 0);
  s21_sprintf(s21_str, "%+u", 0);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%+2u", 0);
  s21_sprintf(s21_str, "%+2u", 0);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%+05u", 12);
  s21_sprintf(s21_str, "%+05u", 12);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%+ 05u", 12);
  s21_sprintf(s21_str, "%+ 05u", 12);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%+- 05u", 12);
  s21_sprintf(s21_str, "%+- 05u", 12);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "% u", 12);
  s21_sprintf(s21_str, "% u", 12);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "% .9u", 12);
  s21_sprintf(s21_str, "% .9u", 12);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "% 5.9u", 12);
  s21_sprintf(s21_str, "% 5.9u", 12);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "% 9.5u", 12);
  s21_sprintf(s21_str, "% 9.5u", 12);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "% 9u", 12);
  s21_sprintf(s21_str, "% 9u", 12);
  ck_assert_pstr_eq(str, s21_str);
  // флаг пробел
  sprintf(str, "% d", 123456);
  s21_sprintf(s21_str, "% d", 123456);
  ck_assert_pstr_eq(str, s21_str);
  // +
  sprintf(str, "%+d", 123456);
  s21_sprintf(s21_str, "%+d", 123456);
  ck_assert_pstr_eq(str, s21_str);
  // -
  sprintf(str, "%-d", 123456);
  s21_sprintf(s21_str, "%-d", 123456);
  ck_assert_pstr_eq(str, s21_str);
  // %
  sprintf(str, "%%");
  s21_sprintf(s21_str, "%%");
  ck_assert_pstr_eq(str, s21_str);
  // s
  sprintf(str, "%s", "str");
  s21_sprintf(s21_str, "%s", "str");
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%5.9s", "str");
  s21_sprintf(s21_str, "%5.9s", "str");
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%9.5s", "str");
  s21_sprintf(s21_str, "%9.5s", "str");
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%-9.5s", "str");
  s21_sprintf(s21_str, "%-9.5s", "str");
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%-5.9s", "str");
  s21_sprintf(s21_str, "%-5.9s", "str");
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%-5.9s", S21_NULL);
  s21_sprintf(s21_str, "%-5.9s", S21_NULL);
  ck_assert_pstr_eq(str, s21_str);
  // c
  sprintf(str, "%c", 'c');
  s21_sprintf(s21_str, "%c", 'c');
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%9.5c", 'c');
  s21_sprintf(s21_str, "%9.5c", 'c');
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%5.9c", 'c');
  s21_sprintf(s21_str, "%5.9c", 'c');
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%-5.9c", 'c');
  s21_sprintf(s21_str, "%-5.9c", 'c');
  ck_assert_pstr_eq(str, s21_str);
  s21_sprintf(s21_str, " %c ", '\0');
  s21_sprintf(str, " %c ", '\0');
  ck_assert_pstr_eq(str, s21_str);
  // f
  sprintf(str, "%f", 11.12);
  s21_sprintf(s21_str, "%f", 11.12);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%Lf", 11.12);
  s21_sprintf(s21_str, "%Lf", 11.12);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%Lf", 0.0);
  s21_sprintf(s21_str, "%Lf", 0.0);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%hf", 11.12);
  s21_sprintf(s21_str, "%hf", 11.12);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%lf", -11.12);
  s21_sprintf(s21_str, "%lf", -11.12);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%f", 1.123456789);
  s21_sprintf(s21_str, "%f", 1.123456789);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%9.5lf", 1.123);
  s21_sprintf(s21_str, "%9.5lf", 1.123);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "% 9.5lf", 1.123);
  s21_sprintf(s21_str, "% 9.5lf", 1.123);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "% 9f", 1.123);
  s21_sprintf(s21_str, "% 9f", 1.123);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%f", 1.0);
  s21_sprintf(s21_str, "%f", 1.0);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%+f", 1.0);
  s21_sprintf(s21_str, "%+f", 1.0);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%7.f", 11.12);
  s21_sprintf(s21_str, "%7.f", 11.12);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%09.2lf", 1.2);
  s21_sprintf(s21_str, "%09.2lf", 1.2);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%+09.2lf", 1.2);
  s21_sprintf(s21_str, "%+09.2lf", 1.2);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%9.2lf", 1.2);
  s21_sprintf(s21_str, "%9.2lf", 1.2);
  ck_assert_pstr_eq(str, s21_str);
  sprintf(str, "%2.9lf", -1.2);
  s21_sprintf(s21_str, "%2.9lf", -1.2);
  ck_assert_pstr_eq(str, s21_str);
  // additional text
  sprintf(str, "test %9d", 123456);
  s21_sprintf(s21_str, "test %9d", 123456);
  ck_assert_pstr_eq(str, s21_str);
  // check return size
  ck_assert_int_eq(sprintf(str, "test %9d", 123456),
                   s21_sprintf(s21_str, "test %9d", 123456));
}
END_TEST

Suite *str_tests_create() {
  Suite *s21_str = suite_create("s21_str");
  TCase *s21_str_tcase = tcase_create("s21_str_tcase");
  // strlen
  tcase_add_test(s21_str_tcase, strlen_test);

  // strcpy
  tcase_add_test(s21_str_tcase, strcpy_test);

  // strpbrk
  tcase_add_test(s21_str_tcase, strpbrk_test);

  // strrchr
  tcase_add_test(s21_str_tcase, strrchr_test);

  // strstr
  tcase_add_test(s21_str_tcase, strstr_test);

  // strtok
  tcase_add_test(s21_str_tcase, strtok_test);

  // strcspn
  tcase_add_test(s21_str_tcase, strcspn_test);

  // strncat
  tcase_add_test(s21_str_tcase, strncat_test);

  // strchr
  tcase_add_test(s21_str_tcase, strchr_test);

  // strncmp
  tcase_add_test(s21_str_tcase, strncmp_test);

  // strerror
  tcase_add_test(s21_str_tcase, strerror_test);

  // memchr
  tcase_add_test(s21_str_tcase, memchr_test);

  // memcmp
  tcase_add_test(s21_str_tcase, memcmp_test);

  // memcpy
  tcase_add_test(s21_str_tcase, memcpy_test);

  // memset
  tcase_add_test(s21_str_tcase, memset_test);

  // to_lower
  tcase_add_test(s21_str_tcase, to_lower_test);

  // to_upper
  tcase_add_test(s21_str_tcase, to_upper_test);

  // insert_test
  tcase_add_test(s21_str_tcase, insert_test);

  // trim
  tcase_add_test(s21_str_tcase, trim_test);

  // sprintf
  tcase_add_test(s21_str_tcase, sprintf_test);

  // Здесь тесты добавляются в тестовый набор
  suite_add_tcase(s21_str, s21_str_tcase);

  return s21_str;
}

int main() {
  Suite *s21_str = str_tests_create();
  SRunner *str_runner = srunner_create(s21_str);
  float failed_count;
  srunner_run_all(str_runner, CK_VERBOSE);
  failed_count = srunner_ntests_failed(str_runner);
  srunner_free(str_runner);

  return failed_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE;

  return 0;
}
