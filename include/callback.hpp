#ifndef CALLBACK_H
#define CALLBACK_H

#include <functional>
#include <memory>
#include <string>

class CallbackClass : public std::enable_shared_from_this<CallbackClass> {
public:
  void set_callback() {
    auto self = shared_from_this();
    callback = [self]() -> std::string { return "Callback function called"; };
  }

  std::string call_callback() {
    if (callback) {
      return callback();
    } else {
      return "Callback function not set";
    }
  }

private:
  std::function<std::string()> callback;
};

#endif
