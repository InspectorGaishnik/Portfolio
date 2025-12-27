OBJ_DIR = object
LIB_DIR = library
TESTS_DIR = tests
GCOV_REPORT_DIR = gcov_report
MAIN_FLAGS = -Wall -Werror -Wextra
TESTS_FLAGS = -lcheck -lm -lsubunit
GCOV_REPORT_FLAGS = -lcheck -lm -lsubunit -fprofile-arcs -ftest-coverage


all: danya_decimal.a


danya_decimal.a:
	gcc $(MAIN_FLAGS) -c danya_additional.c -o $(OBJ_DIR)/danya_additional.o
	gcc $(MAIN_FLAGS) -c danya_decimal.c -o $(OBJ_DIR)/danya_decimal.o
	ar r $(LIB_DIR)/danya_decimal.a $(OBJ_DIR)/*.o


test:
	gcc $(MAIN_FLAGS) tests.c danya_decimal.c danya_additional.c -o $(TESTS_DIR)/run_tests $(TESTS_FLAGS)


gcov_report:
	gcc $(MAIN_FLAGS) tests.c danya_decimal.c danya_additional.c $(GCOV_REPORT_FLAGS) -o $(GCOV_REPORT_DIR)/run_tests_gcov
	$(GCOV_REPORT_DIR)/./run_tests_gcov
	rm -f $(GCOV_REPORT_DIR)/run_tests_gcov-tests.gcda $(GCOV_REPORT_DIR)/run_tests_gcov-tests.gcno
	gcovr -r . --html --html-details -o $(GCOV_REPORT_DIR)/coverage_report.html


clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(LIB_DIR)/*.a
	rm -f $(GCOV_REPORT_DIR)/*.html 
	rm -f $(GCOV_REPORT_DIR)/*.css
	rm -f $(GCOV_REPORT_DIR)/*.gcda
	rm -f $(GCOV_REPORT_DIR)/*.gcno
	rm -f $(GCOV_REPORT_DIR)/run_tests_gcov
	rm -f $(TESTS_DIR)/run_tests


.PHONY: gcov_report