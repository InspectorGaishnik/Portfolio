MAIN_FLAGS = -Wall -Werror -Wextra
TESTS_FLAGS = -lcheck -lm -lsubunit
GCOV_REPORT_FLAGS = -lcheck -lm -lsubunit -fprofile-arcs -ftest-coverage
OBJ_DIR = objectFiles
LIB_DIR = library
TEST_DIR = tests
GCOV_REPORT_DIR = gcov_report


all: danya_matrix.a


danya_matrix.a:
	gcc $(MAIN_FLAGS) -c danya_matrix.c -o $(OBJ_DIR)/danya_matrix.o
	ar r danya_matrix.a $(OBJ_DIR)/*.o


test: 
	checkmk clean_mode=1 tests.check > tests.c
	gcc $(MAIN_FLAGS) tests.c danya_matrix.c $(TESTS_FLAGS) -o $(TEST_DIR)/run_tests
	./tests/run_tests


gcov_report:
	gcc $(MAIN_FLAGS) tests.c danya_matrix.c $(GCOV_REPORT_FLAGS) -o $(GCOV_REPORT_DIR)/run_tests_gcov
	$(GCOV_REPORT_DIR)/./run_tests_gcov
	rm -f $(GCOV_REPORT_DIR)/run_tests_gcov-tests.gcda $(GCOV_REPORT_DIR)/run_tests_gcov-tests.gcno
	gcovr -r . --html --html-details -o $(GCOV_REPORT_DIR)/coverage_report.html


clean:
	rm -f danya_matrix.a
	rm -f $(LIB_DIR)/*.a
	rm -f $(OBJ_DIR)/*.o
	rm -f $(TEST_DIR)/run_tests
	rm -f $(GCOV_REPORT_DIR)/*.css
	rm -f $(GCOV_REPORT_DIR)/*.html
	rm -f $(GCOV_REPORT_DIR)/*.gcda
	rm -f $(GCOV_REPORT_DIR)/*.gcno
	rm -f $(GCOV_REPORT_DIR)/run_tests_gcov


.PHONY: all danya_matrix.a test clean gcov_report
