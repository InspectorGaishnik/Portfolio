C_FILES = 														  \
$(TESTS_DIR)/tests.c $(C_FILES_DIR)/danya_c_sharp_func.c 		  \
$(C_FILES_DIR)/danya_common_func.c $(C_FILES_DIR)/danya_sprintf.c \
$(C_FILES_DIR)/danya_sscanf.c $(C_FILES_DIR)/danya_string.c 	  \
$(C_FILES_DIR)/danya_strtold.c


MAIN_FLAGS = -Wall -Werror -Wextra -std=c11
TESTS_FLAGS = -lcheck -lm -lsubunit -std=c11
GCOV_REPORT_FLAGS = -lcheck -lm -lsubunit -fprofile-arcs -ftest-coverage -std=c11


OBJ_DIR = objectFiles
TESTS_DIR = tests
GCOV_REPORT_DIR = gcov_report
C_FILES_DIR = C-files


all: danya_string.a


danya_string.a:
	mkdir -p $(OBJ_DIR)
	gcc $(MAIN_FLAGS) -c $(C_FILES_DIR)/danya_c_sharp_func.c -o $(OBJ_DIR)/danya_c_sharp_func.o
	gcc $(MAIN_FLAGS) -c $(C_FILES_DIR)/danya_common_func.c -o $(OBJ_DIR)/danya_common_func.o
	gcc $(MAIN_FLAGS) -c $(C_FILES_DIR)/danya_sprintf.c -o $(OBJ_DIR)/danya_sprintf.o
	gcc $(MAIN_FLAGS) -c $(C_FILES_DIR)/danya_sscanf.c -o $(OBJ_DIR)/danya_sscanf.o
	gcc $(MAIN_FLAGS) -c $(C_FILES_DIR)/danya_string.c -o $(OBJ_DIR)/danya_string.o
	gcc $(MAIN_FLAGS) -c $(C_FILES_DIR)/danya_strtold.c -o $(OBJ_DIR)/danya_strtold.o
	ar r danya_string.a $(OBJ_DIR)/*.o


test:
	gcc $(MAIN_FLAGS) $(C_FILES) $(TESTS_FLAGS) -o $(TESTS_DIR)/run_tests
	./$(TESTS_DIR)/run_tests


gcov_report:
	mkdir -p $(GCOV_REPORT_DIR)
	gcc $(MAIN_FLAGS) $(C_FILES) $(GCOV_REPORT_FLAGS) -o $(GCOV_REPORT_DIR)/run_tests_gcov
	./$(GCOV_REPORT_DIR)/run_tests_gcov
	gcovr -r . --html --html-details \
	--exclude '$(TESTS_DIR)/tests.c' \
	-o $(GCOV_REPORT_DIR)/coverage_report.html


clean:
	rm -f danya_string.a
	rm -rf $(OBJ_DIR)
	rm -f $(TESTS_DIR)/run_tests
	rm -rf $(GCOV_REPORT_DIR)

.PHONY: all danya_string.a test gcov_report clean