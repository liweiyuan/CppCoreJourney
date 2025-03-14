#ifndef CONVERT_STRING_HPP
#define CONVERT_STRING_HPP

#include <algorithm>
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
        std::istringstream iss(str); // 用字符串初始化输入流
        T result;
        iss >>
            result; // 使用 >>
                    // 进行类型转换,因为大部分类型都支持这个操作符(int,double,bool等)
        // 检查转换是否成功，并且确保流已到达末尾（防止部分转换）
        if (!iss.fail() && iss.eof()) {
            return result;
        }
        return std::nullopt;
    }

    // 特化 bool 类型处理
    template <> std::optional<bool> to() const {
        // 创建小写副本用于布尔解析
        std::string lower_str;
        std::transform(str.begin(), str.end(), std::back_inserter(lower_str),
                       [](unsigned char c) { return std::tolower(c); });
        // 使用转换后的字符串
        std::istringstream iss(lower_str);
        bool result;

        // 尝试解析 "true"/"false"（严格区分大小写）
        iss >> std::boolalpha >> result;
        iss >> std::ws; // 消耗流中可能存在的空白字符
        if (!iss.fail() && iss.eof()) {
            return result;
        }

        // 尝试解析数字格式
        iss.clear();
        iss.seekg(0);
        int num;
        if (iss >> num) {
            iss >> std::ws; // 同样消耗尾部空白
            if (iss.eof()) {
                return num != 0;
            }
        }

        return std::nullopt;
    }

    // 特化 string 类型处理
    template <> std::optional<std::string> to() const {
        // 直接返回原始字符串
        return str;
    }
};
#endif

/**
 ConvertString::to<T>() 能进行类型转换的关键

std::istringstream 允许从字符串解析数据，类似 std::cin 读取输入。
operator>> 在 std::istringstream 上被重载，适用于 int、float、double
等基本类型。 通过 iss.fail() 检测是否转换失败。 使用 iss.eof()
确保完整转换，防止 std::istringstream 解析部分字符串但仍返回成功。
代码提供了安全的字符串转换方案

std::optional<T> 使转换更安全，避免错误值返回。
iss.eof() 确保完整转换，防止部分数据误解析。
这种设计让 ConvertString 可以泛型化地处理不同的类型转换，适用于
数字解析、配置文件解析等场景。



*/