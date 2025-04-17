#include <algorithm>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <random>

struct LogEntry {
    std::string timestamp;
    char site_id;
    int value;

    bool operator<(const LogEntry &other) const {
        return timestamp < other.timestamp;
    }
};

std::string make_timestamp(int base_seconds) {
    int h = base_seconds / 3600;
    int m = (base_seconds % 3600) / 60;
    int s = base_seconds % 60;

    // 还需添加年月日
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "2025-04-15 %02d:%02d:%02d", h, m, s);
    return std::string(buffer);
}
void generate_log_file(const std::string &filename, int site_id, int start,
                       int interval, int count) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }
    std::mt19937 rng(site_id);
    std::uniform_int_distribution<int> dist(10, 100);
    for (int i = 0; i < count; i++) {
        int value = dist(rng);
        std::string timestamp = make_timestamp(start + i * interval);
        file << timestamp << " " << site_id << " " << value << "\n";
    }
}

std::vector<LogEntry> read_log_file(const std::string &filename) {
    std::ifstream in(filename);
    std::vector<LogEntry> logs;
    std::string ts;
    char site;
    int value;

    while (in >> std::ws && std::getline(in, ts, ' ')) {
        std::string time_part;
        in >> time_part >> site >> value;
        logs.push_back({ts + " " + time_part, site, value});
    }

    return logs;
}

void write_merged_log(const std::string &filename,
                      const std::vector<LogEntry> &entries) {
    std::ofstream out(filename);
    for (const auto &entry : entries) {
        out << entry.timestamp << " " << entry.site_id << " " << entry.value
            << "\n";
    }
}

// 测试合并
TEST(MergeTest, MergeLogs) {
    // Step 1: Generate site A and B logs
    generate_log_file("siteA.log", 'A', 3600, 60,
                      10); // start at 01:00:00, every 1 min
    generate_log_file("siteB.log", 'B', 3660, 90,
                      10); // start at 01:01:00, every 1.5 min

    // Step 2: Read logs back into vectors
    auto logsA = read_log_file("siteA.log");
    auto logsB = read_log_file("siteB.log");

    // Step 3: Merge logs using std::merge
    std::vector<LogEntry> merged(logsA.size() + logsB.size());
    std::merge(logsA.begin(), logsA.end(), logsB.begin(), logsB.end(),
               merged.begin());

    // Step 4: Write merged result
    write_merged_log("merged.log", merged);
    // Step 5: Read merged log and check the order
    auto mergedLogs = read_log_file("merged.log");
    for (size_t i = 1; i < mergedLogs.size(); ++i) {
        // 打印
        std::cout << mergedLogs[i].timestamp << " " << mergedLogs[i].site_id
                  << " " << mergedLogs[i].value << "\n";
    }

    // 删除文件
    std::remove("siteA.log");
    std::remove("siteB.log");
    std::remove("merged.log");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}