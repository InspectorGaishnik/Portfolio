CC 			  = gcc


MAIN_FLAGS    = -Wall -Werror -Wextra -std=c++20
TESTS_FLAGS   = -lgtest -lgtest_main -lm -lstdc++
GCOV_FLAGS    = -lgtest -lgtest_main -lm -lstdc++ -fprofile-arcs -ftest-coverage
SPECIAL_FLAGS = -lstdc++


OBJ_DIR 	  = ObjectFiles
TEST_DIR      = tests
GCOV_DIR 	  = gcov_report
CLANG_DIR 	  = clang_format
SRC_DIR 	  = src
DIST_DIR 	  = my_project_matrix_cpp_1.0


TEST_FILES    = $(TEST_DIR)/tests.cpp $(TEST_DIR)/tests_operators.cpp $(TEST_DIR)/tests_constructors.cpp


all: s21_matrix_oop.a


s21_matrix_oop.a: 
	mkdir -p $(OBJ_DIR)
	$(CC) $(MAIN_FLAGS) -c s21_matrix_oop.cpp -o $(OBJ_DIR)/s21_matrix_oop.o
	ar r s21_matrix_oop.a $(OBJ_DIR)/*.o


test: 
	$(CC) $(MAIN_FLAGS) $(TEST_DIR)/tests.cpp s21_matrix_oop.cpp $(TESTS_FLAGS) -o $(TEST_DIR)/run_tests.out
	$(CC) $(MAIN_FLAGS) $(TEST_DIR)/tests_operators.cpp s21_matrix_oop.cpp $(TESTS_FLAGS) -o $(TEST_DIR)/run_tests_operators.out
	$(CC) $(MAIN_FLAGS) $(TEST_DIR)/tests_constructors.cpp s21_matrix_oop.cpp $(TESTS_FLAGS) -o $(TEST_DIR)/run_tests_constructors.out
	./$(TEST_DIR)/run_tests.out
	./$(TEST_DIR)/run_tests_operators.out
	./$(TEST_DIR)/run_tests_constructors.out


valgrind: test	
	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST_DIR)/run_tests.out
	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST_DIR)/run_tests_operators.out
	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST_DIR)/run_tests_constructors.out


gcov_report: 
	mkdir -p $(GCOV_DIR)
	$(CC) $(MAIN_FLAGS) $(TEST_FILES) s21_matrix_oop.cpp $(GCOV_FLAGS) -o $(GCOV_DIR)/run_tests_gcov.out
	./$(GCOV_DIR)/run_tests_gcov.out
	gcovr -r . --html --html-details 			   \
	--exclude '$(TEST_DIR)/tests.cpp' 			   \
	--exclude '$(TEST_DIR)/tests_operators.cpp'    \
	--exclude '$(TEST_DIR)/tests_constructors.cpp' \
	-o $(GCOV_DIR)/coverage_report.html


dist:
	mkdir -p ../$(DIST_DIR)
	cp -r ../src ../$(CLANG_DIR) ../$(DIST_DIR)/
	tar -czf $(DIST_DIR).tar.gz ../$(DIST_DIR) 
	rm -rf ../$(DIST_DIR)


clang_format:
	@mv ../$(CLANG_DIR)/.clang-format .././$(SRC_DIR)
	clang-format -i *.h *.cpp
	clang-format -n *.h *.cpp
	clang-format -i $(TEST_DIR)/*.cpp
	clang-format -n $(TEST_DIR)/*.cpp
	@mv .clang-format .././$(CLANG_DIR)


clean:
	rm -f main.out
	rm -f $(TEST_DIR)/run_tests.out
	rm -f $(TEST_DIR)/run_tests_operators.out
	rm -f $(TEST_DIR)/run_tests_constructors.out
	rm -rf $(OBJ_DIR)
	rm -rf $(GCOV_DIR)
	rm -f $(GCOV_DIR)/*.gcda
	rm -f $(GCOV_DIR)/*.gcno
	rm -f s21_matrix_oop.a


.PHONY: all s21_matrix_oop.a test valgrind gcov_report run clang_format clean