ifeq ($(OS),Windows_NT)
	RM = del /F /Q
	EXE_EXT = .exe
	RUN = 
else
	RM = rm -f
	EXE_EXT =
	RUN = ./
endif

all: test

test:
	g++ tests_MalwareDatabase.cpp -o tests_MalwareDatabase$(EXE_EXT) -lgtest -lgtest_main -lm -pthread
	g++ tests_MD5Hasher.cpp -o tests_MD5Hasher$(EXE_EXT) -lgtest -lgtest_main -lm -pthread
	g++ tests_Scanner.cpp -o tests_Scanner$(EXE_EXT) -lgtest -lgtest_main -lm -pthread
	$(RUN)tests_MalwareDatabase$(EXE_EXT)
	$(RUN)tests_MD5Hasher$(EXE_EXT)
	$(RUN)tests_Scanner$(EXE_EXT)

test_MalwareDatabase:
	g++ tests_MalwareDatabase.cpp -o tests_MalwareDatabase$(EXE_EXT) -lgtest -lgtest_main -lm -pthread
	$(RUN)tests_MalwareDatabase$(EXE_EXT)

test_MD5Hasher:
	g++ tests_MD5Hasher.cpp -o tests_MD5Hasher$(EXE_EXT) -lgtest -lgtest_main -lm -pthread
	$(RUN)tests_MD5Hasher$(EXE_EXT)

test_Scanner:
	g++ tests_Scanner.cpp -o tests_Scanner$(EXE_EXT) -lgtest -lgtest_main -lm -pthread
	$(RUN)tests_Scanner$(EXE_EXT)

clean:
	$(RM) tests_MalwareDatabase$(EXE_EXT)
	$(RM) tests_MD5Hasher$(EXE_EXT)
	$(RM) tests_Scanner$(EXE_EXT)
