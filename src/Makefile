CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
TEST_FLAGS = -lcheck -lpthread -lm
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
MATRIX = s21_matrix.a 
TESTS_OBJECT = s21_matrix_test

OS:=$(shell uname -s)
ifeq ($(OS), Linux)
 TEST_FLAGS += -lsubunit -lrt
endif

all: clean s21_matrix.a test gcov_report

s21_matrix.a:
	$(CC) $(CFLAGS) s21_*.c -c
	ar rcs $(MATRIX) *.o
	ranlib $(MATRIX)
	rm -rf *.o
	
rebuild: clean s21_matrix.a

test: s21_matrix.a
	$(CC) $(CFLAGS) tests/*.c s21_*.c  -o $(TESTS_OBJECT) $(TEST_FLAGS) $(GCOV_FLAGS)
	./$(TESTS_OBJECT) > tests/$(TESTS_OBJECT).log
	cat tests/$(TESTS_OBJECT).log

gcov_report: s21_matrix.a test 
	lcov -t "$(TESTS_OBJECT)" -o $(TESTS_OBJECT).info -c -d .
	genhtml -o report $(TESTS_OBJECT).info
	open report/index.html
	rm -rf *.gcda *.gcno

clean:
	rm -rf *.gcda *.gcno *.info s21_matrix *.a *.o s21_matrix_test report tests/*.log valgrind_fails.log

clang:
	clang-format -n *.c *.h tests/*.c *.h
	clang-format -i *.c *.h tests/*.c *.h

cppcheck:
	cppcheck s21_*.c tests/*c --enable=all --suppress=missingIncludeSystem

valgrind: clean
	$(CC) $(CFLAGS) -g tests/*.c s21_*.c  -o $(TESTS_OBJECT) $(TEST_FLAGS) $(GCOV_FLAGS)
	valgrind --leak-check=full --tool=memcheck --track-origins=yes --quiet --log-file=valgrind_fails.log ./$(TESTS_OBJECT)
	rm -rf *.gcda *.gcno
