/*
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug
*/

#include <iostream>

#include "MalwareScanner.h"

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr
        << "Использование: ScannerCLI <директория> <csv база> <файл лога>\n";
    return 1;
  }

  if (!InitializeScanner(argv[2], argv[3])) {
    std::cerr << "Ошибка инициализации сканера\n";
    return 1;
  }

  if (!StartScan(argv[1])) {
    std::cerr << "Ошибка запуска сканирования\n";
    CleanupScanner();
    return 1;
  }

  const char* report = GetScanReport();
  std::cout << report;

  CleanupScanner();
  return 0;
}
