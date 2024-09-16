CC = gcc -Wall -Werror -Wextra
GCOVFLAGS = -fprofile-arcs -ftest-coverage

ifeq ($(shell uname -s), Darwin)
	LIB = -lcheck -lm -lpthread -lgcov
endif

ifeq ($(shell uname -s), Linux)
	LIB = -lcheck -lsubunit -lm -lrt -lpthread -lgcov
endif

all: clean s21_string.a test gcov_report

clean:
	rm -rf *.o *.a out *.info *.gcda *.gcno *.gcov *.gch *.out test report

test:
	gcc $(GCOVFLAGS)  */s21_*.c unit_test/test.c $(LIB) -o test
	./test

s21_string.a:
	$(CC) -std=c11 -c ./*/s21_*.c
	ar rc s21_string.a *.o 

gcov_report: s21_string.a
	gcov test-test.c
	lcov -t "gcov_report" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info