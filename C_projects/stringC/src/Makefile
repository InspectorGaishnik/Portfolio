C_FILES = tests.c danya_c_sharp_func.c danya_common_func.c danya_sprintf.c danya_sscanf.c danya_string.c danya_strtold.c
OBJ_DIR = objectFiles
LIB_DIR = library
TESTS_DIR = tests
GCOV_REPORT_DIR = gcov_report
MAIN_FLAGS = -Wall -Werror -Wextra
TESTS_FLAGS = -lcheck -lm -lsubunit
GCOV_REPORT_FLAGS = -lcheck -lm -lsubunit -fprofile-arcs -ftest-coverage


all: danya_string.a


danya_string.a:
	gcc $(MAIN_FLAGS) -c danya_c_sharp_func.c -o $(OBJ_DIR)/danya_c_sharp_func.o
	gcc $(MAIN_FLAGS) -c danya_common_func.c -o $(OBJ_DIR)/danya_common_func.o
	gcc $(MAIN_FLAGS) -c danya_sprintf.c -o $(OBJ_DIR)/danya_sprintf.o
	gcc $(MAIN_FLAGS) -c danya_sscanf.c -o $(OBJ_DIR)/danya_sscanf.o
	gcc $(MAIN_FLAGS) -c danya_string.c -o $(OBJ_DIR)/danya_string.o
	gcc $(MAIN_FLAGS) -c danya_strtold.c -o $(OBJ_DIR)/danya_strtold.o
	ar r $(LIB_DIR)/danya_string.a $(OBJ_DIR)/*.o


test:
	gcc $(MAIN_FLAGS) $(C_FILES) $(TESTS_FLAGS) -o $(TESTS_DIR)/run_tests


gcov_report:
	gcc $(MAIN_FLAGS) $(C_FILES) $(GCOV_REPORT_FLAGS) -o $(GCOV_REPORT_DIR)/run_tests_gcov
	$(GCOV_REPORT_DIR)/./run_tests_gcov
	rm -f $(GCOV_REPORT_DIR)/run_tests_gcov-tests.gcda $(GCOV_REPORT_DIR)/run_tests_gcov-tests.gcno
	gcovr -r . --html --html-details -o $(GCOV_REPORT_DIR)/coverage_report.html


clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(LIB_DIR)/*.a
	rm -f $(GCOV_REPORT_DIR)/*.css
	rm -f $(GCOV_REPORT_DIR)/c*.html
	rm -f $(GCOV_REPORT_DIR)/*.gcda
	rm -f $(GCOV_REPORT_DIR)/*.gcno
	rm -f $(GCOV_REPORT_DIR)/run_tests_gcov
	rm -f $(TESTS_DIR)/run_tests


.PHONY: gcov_report