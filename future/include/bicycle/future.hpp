#pragma once

#include <atomic>
#include <concepts
#include <exception>
#include <variant>
#include <mutex>
#include <condition_variable>
#include <functional>


namespace bicycle::future {

template <typename T, typename Arg>
concept Continuation = requires(T callable, Arg arg) {
  std::invocable<T>;
  { callable(arg) } -> std::convertible_to<>;
};

template <typename T>
class Future {
 public:
  template <typename F>
  std::invoke_result_t<F> Then(F f) {
  }

  template <typename F>
  std::invoke_result_t<F> Then(F f) {

  }

 private:
  std::function<>;
};

}  // namespace bicycle::future
