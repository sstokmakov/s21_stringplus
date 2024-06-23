CC= gcc 
CFLAGS= -Wall -Werror -Wextra -std=c11          
TFLAGS = -lcheck -lpthread -lm
TEST=s21_test
OPEN = open

ifeq ($(shell uname), Linux)
	OPEN = xdg-open
	TFLAGS += -lrt -lsubunit -lgcov
endif

all: s21_string.a

clean:
	rm -rf *.a && rm -rf *.gcda
	rm -rf *.o && rm -rf *.gcno
	rm -rf report && rm -rf *.info  
	rm -rf $(TEST)
               
test: s21_string.a
	$(CC) -o $(TEST) $(TEST).c  s21_string.a $(TFLAGS) 
	./$(TEST)

s21_string.a:
	$(CC)  -c s21_string.c -o s21_string.o
	ar rcs s21_string.a s21_string.o
	ranlib s21_string.a

gcov_report: 
	$(CC) --coverage -o $(TEST) $(TEST).c s21_string.c $(TFLAGS)   
	./$(TEST)
	lcov -t "$(TEST)" -o $(TEST).info -c -d . --rc branch_coverage=1
	genhtml -o report $(TEST).info --rc branch_coverage=1
	open ./report/index.html

rebuild: clean all
