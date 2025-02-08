#ifndef STATE_HPP
#define STATE_HPP

#include <iostream>
#include <string>
#include <variant>

class BaseState {
public:
  virtual ~BaseState() = default;
  virtual std::string name() const = 0;
};

class Idle : public BaseState {

public:
  std::string name() const override { return "Idle"; }
};

class Processing : public BaseState {
  std::string name() const override { return "Processing"; }
};

class Completed : public BaseState {
  std::string name() const override { return "Completed"; }
};

using State = std::variant<Idle, Processing, Completed>;

enum class Event {
  Start,
  Complete,
  Reset,
};

class FSM {
public:
  FSM() : currentState(Idle{}) {}

  void handleEvent(Event event) {
    std::visit(
        [this, event](auto &&state) {
          using StateType = std::decay_t<decltype(state)>;
          if constexpr (std::is_same_v<StateType, Idle>) {
            if (event == Event::Start) {
              currentState = Processing{};
              std::cout << "Transitioned to Processing state." << std::endl;
            }
          } else if constexpr (std::is_same_v<StateType, Processing>) {
            if (event == Event::Complete) {
              currentState = Completed{};
              std::cout << "Transitioned to Completed state." << std::endl;
            } else if (event == Event::Reset) {
              currentState = Idle{};
              std::cout << "Transitioned back to Idle state." << std::endl;
            }
          } else if constexpr (std::is_same_v<StateType, Completed>) {
            if (event == Event::Reset) {
              currentState = Idle{};
              std::cout << "Reset to Idle state." << std::endl;
            }
          }
        },
        currentState);
  }

  // 获取当前状态
  const State &getCurrentState() const { return currentState; }

private:
  State currentState;
};
#endif