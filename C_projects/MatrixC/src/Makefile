MAIN_FLAGS = -Wall -Werror -Wextra -std=c11
TESTS_FLAGS = -lcheck -lm -lsubunit -std=c11
GCOV_REPORT_FLAGS = -lcheck -lm -lsubunit -fprofile-arcs -ftest-coverage -std=c11
OBJ_DIR = objectFiles
TEST_DIR = tests
GCOV_REPORT_DIR = gcov_report


all: danya_matrix.a


danya_matrix.a:
	mkdir -p $(OBJ_DIR)
	gcc $(MAIN_FLAGS) -c danya_matrix.c -o $(OBJ_DIR)/danya_matrix.o
	ar r danya_matrix.a $(OBJ_DIR)/*.o


test: 
	mkdir -p $(TEST_DIR)
	checkmk clean_mode=1 tests.check > $(TEST_DIR)/tests.c
	gcc $(MAIN_FLAGS) $(TEST_DIR)/tests.c danya_matrix.c $(TESTS_FLAGS) -o $(TEST_DIR)/run_tests
	./$(TEST_DIR)/run_tests


gcov_report: test
	mkdir -p $(GCOV_REPORT_DIR)
	gcc $(MAIN_FLAGS) $(TEST_DIR)/tests.c danya_matrix.c $(GCOV_REPORT_FLAGS) -o $(GCOV_REPORT_DIR)/run_tests_gcov
	$(GCOV_REPORT_DIR)/./run_tests_gcov
	gcovr -r . --html --html-details \
	--exclude '$(TEST_DIR)/tests.c' \
	-o $(GCOV_REPORT_DIR)/coverage_report.html


clean:
	rm -f danya_matrix.a
	rm -rf $(OBJ_DIR)
	rm -rf $(TEST_DIR)
	rm -rf $(GCOV_REPORT_DIR)

.PHONY: all danya_matrix.a test clean gcov_report
