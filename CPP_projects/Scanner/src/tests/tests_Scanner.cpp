#include <gtest/gtest.h>

#include "../MalwareScanner.cpp"

TEST(ScannerIntegrationTest, ScanExistingData) {
    std::string csvPath = "../malicious_hashe.csv";
    std::string scanDir = "../directory";
    std::string logPath = "../log.txt";

    MalwareDatabase db;
    ASSERT_TRUE(db.loadFromCSV(csvPath));

    Logger logger;
    ASSERT_TRUE(logger.open(logPath));

    Scanner scanner(db, logger);
    scanner.scanDirectory(scanDir);

    EXPECT_GT(scanner.getTotalFilesCount(), 0);

    EXPECT_LE(scanner.getErrorFilesCount(), scanner.getTotalFilesCount());
}
