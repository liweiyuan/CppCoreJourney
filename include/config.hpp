#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <any>
#include <map>
#include <string>
#include <utility>
class Config {
public:
  template <typename T> void set(const std::string &key, T &&value) {
    m_data[key] = std::forward<T>(value);
  }

  template <typename T> T get(const std::string &key) {
    return std::any_cast<T>(m_data.at(key));
  }

private:
  std::map<std::string, std::any> m_data;
};
#endif