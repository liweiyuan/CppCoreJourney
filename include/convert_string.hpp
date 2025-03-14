#ifndef CONVERT_STRING_HPP
#define CONVERT_STRING_HPP

#include <optional>
#include <sstream>
#include <string>

class ConvertString {
  private:
    std::string str;

  public:
    explicit ConvertString(const std::string &str) : str(str) {}

    // 转换为T类型
    template <typename T> std::optional<T> to() const {
        std::istringstream iss(str);
        T result;
        iss >> result;
        // 检查是否成功转换并且到达流的末尾
        if (!iss.fail() && iss.eof()) {
            return result;
        }
        return std::nullopt;
    }
};
#endif