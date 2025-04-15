#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <string>

namespace fs = std::filesystem;

class FileSystemTest : public ::testing::Test {
  protected:
    fs::path test_dir;
    fs::path test_file;

    void SetUp() override {
        test_dir = fs::temp_directory_path() / "test_dir";
        fs::create_directories(test_dir);
        test_file = test_dir / "test_file.txt";
    }

    void TearDown() override {
        if (fs::exists(test_dir)) {
            fs::remove_all(test_dir);
        }
    }
};

TEST_F(FileSystemTest, DirectoryCreationAndRemoval) {
    EXPECT_TRUE(fs::exists(test_dir));
    EXPECT_TRUE(fs::is_directory(test_dir));
    fs::remove(test_dir);
    EXPECT_FALSE(fs::exists(test_dir));
}

TEST_F(FileSystemTest, FileCreationAndRemoval) {
    // 创建文件
    std::ofstream ofs(test_file);
    ofs << "Hello, World!";
    ofs.close();
    EXPECT_TRUE(fs::exists(test_file));
    EXPECT_TRUE(fs::is_regular_file(test_file));

    // 读取内容
    std::ifstream ifs(test_file);
    std::string content;
    std::getline(ifs, content);
    EXPECT_EQ(content, "Hello, World!");

    fs::remove(test_file);
    EXPECT_FALSE(fs::exists(test_file));
}

TEST_F(FileSystemTest, FileRenameAndRemove) {
    std::ofstream ofs(test_file);
    ofs << "test";
    ofs.close();

    fs::path new_file = test_dir / "renamed.txt";
    fs::rename(test_file, new_file);
    EXPECT_FALSE(fs::exists(test_file));
    EXPECT_TRUE(fs::exists(new_file));

    fs::remove(new_file);
    EXPECT_FALSE(fs::exists(new_file));
}

TEST_F(FileSystemTest, DirectoryIterator) {
    // 创建多个文件
    for (int i = 0; i < 3; ++i) {
        std::ofstream ofs(test_dir / ("f" + std::to_string(i) + ".txt"));
        ofs << i;
    }
    int file_count = 0;
    for (auto &entry : fs::directory_iterator(test_dir)) {
        if (fs::is_regular_file(entry)) {
            ++file_count;
        }
    }
    EXPECT_EQ(file_count, 3);
}

TEST_F(FileSystemTest, PathManipulation) {
    fs::path p = "/tmp/test/abc.txt";
    EXPECT_EQ(p.filename(), "abc.txt");
    EXPECT_EQ(p.extension(), ".txt");
    EXPECT_EQ(p.parent_path(), "/tmp/test");
    EXPECT_EQ(p.stem(), "abc");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}