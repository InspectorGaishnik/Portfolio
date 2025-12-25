#include <gtest/gtest.h> 

#include "../MalwareScanner.cpp"

TEST(MD5HasherTest, EmptyString) {
    MD5Hasher md5;
    md5.update("");
    EXPECT_EQ(md5.final(), "d41d8cd98f00b204e9800998ecf8427e");
}

TEST(MD5HasherTest, KnownString) {
    MD5Hasher md5;
    md5.update("hello");
    EXPECT_EQ(md5.final(), "5d41402abc4b2a76b9719d911017c592");
}

TEST(MD5HasherTest, My_Doom) {
    MD5Hasher md5;
    md5.update("My Doom");
    EXPECT_EQ(md5.final(), "d88cf4ebda47388279a0a2c45442452c");
}

TEST(MD5HasherTest, Conficker) {
    MD5Hasher md5;
    md5.update("Conficker");
    EXPECT_EQ(md5.final(), "50b01599ede4e93c16045f8b2abab5c3");
}

TEST(MD5HasherTest, CoolWebSearch) {
    MD5Hasher md5;
    md5.update("CoolWebSearch");
    EXPECT_EQ(md5.final(), "22293e48c9872aa12165c18b6eadacce");
}

TEST(MD5HasherTest, Gator) {
    MD5Hasher md5;
    md5.update("Gator");
    EXPECT_EQ(md5.final(), "cb5415ba0348bb81d3749d02c8def6c9");
}

TEST(MD5HasherTest, Zeus) {
    MD5Hasher md5;
    md5.update("Zeus");
    EXPECT_EQ(md5.final(), "98dd15c330fb5abb4508347265a7f76c");
}

TEST(MD5HasherTest, Trojan_Spy_Win32_Noon) {
    MD5Hasher md5;
    md5.update("Trojan-Spy.Win32.Noon");
    EXPECT_EQ(md5.final(), "c8d6a331d7e07e4e0b314e5fdad7b3c3");
}

TEST(MD5HasherTest, SQL_Slammer) {
    MD5Hasher md5;
    md5.update("SQL Slammer");
    EXPECT_EQ(md5.final(), "2d106d2d8f9f03b07cfca22628302f6c");
}

TEST(MD5HasherTest, WannaCry) {
    MD5Hasher md5;
    md5.update("WannaCry");
    EXPECT_EQ(md5.final(), "424a38b21b4ecc0f8cf7f178012ed965");
}

TEST(MD5HasherTest, Locky) {
    MD5Hasher md5;
    md5.update("Locky");
    EXPECT_EQ(md5.final(), "979d3ab6ac0c156ebfb33e9f4d62347c");
}
