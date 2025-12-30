OBJ_DIR = objectFiles
TESTS_DIR = tests
GCOV_REPORT_DIR = gcov_report
MAIN_FLAGS = -Wall -Werror -Wextra
TESTS_FLAGS = -lcheck -lm -lsubunit
GCOV_REPORT_FLAGS = -lcheck -lm -lsubunit -fprofile-arcs -ftest-coverage


all: danya_decimal.a


danya_decimal.a:
	mkdir -p $(OBJ_DIR)
	gcc $(MAIN_FLAGS) -c danya_additional.c -o $(OBJ_DIR)/danya_additional.o
	gcc $(MAIN_FLAGS) -c danya_decimal.c -o $(OBJ_DIR)/danya_decimal.o
	ar r danya_decimal.a $(OBJ_DIR)/*.o


test:
	gcc $(MAIN_FLAGS) $(TESTS_DIR)/tests.c danya_decimal.c danya_additional.c -o $(TESTS_DIR)/run_tests $(TESTS_FLAGS)
	./$(TESTS_DIR)/run_tests


gcov_report:
	mkdir -p $(GCOV_REPORT_DIR)
	gcc $(MAIN_FLAGS) $(TESTS_DIR)/tests.c danya_decimal.c danya_additional.c $(GCOV_REPORT_FLAGS) -o $(GCOV_REPORT_DIR)/run_tests_gcov
	./$(GCOV_REPORT_DIR)/run_tests_gcov
	gcovr -r . --html --html-details \
	--exclude '$(TESTS_DIR)/tests.c' \
	-o $(GCOV_REPORT_DIR)/coverage_report.html


clean:
	rm -f danya_decimal.a
	rm -rf $(OBJ_DIR)
	rm -f $(TESTS_DIR)/run_tests
	rm -rf $(GCOV_REPORT_DIR)

.PHONY: all danya_decimal.a test gcov_report clean