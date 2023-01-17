#pragma once

#include <memory>
#include <type_traits>

namespace bicycle {

/// \brief Container which represents the result of operation call.
/// It either holds a value or an error. If container holds the value, then it methods is TODO:
/// Inspired by [this article]()
template <typename T, typename Error>
class Result {
 public:
  static_assert(!std::is_reference_v<T>, "aaa");

  /// Constructs the result containing an error.
  template <typename... Args>
  static Result Fail(Args&&... args) {
    Error error{std::forward<Args>(args)...};

    return Result(std::move(error));
  }

  /// Creates the result containing value.
  template <typename... Args>
  static Result Ok(Args&&... args) {
    T value{std::forward<Args>(args)...};

    return Result{std::move(value)};
  }

  /// Returns \a true if container contains value, \a false if error.
  bool IsOk() const noexcept {}

  /// Returns
  bool HasError() const noexcept {}

  /// Returns const reference to the error.
  /// \note If container does not contain an error, then assertion will be triggered.
  const Error& GetError() const {}

  /// Returns const reference to a value.
  /// \note If container does not contain a value, then assertion will be triggered.
  const T& GetValue() const {}

  /// Returns reference to an error.
  /// \note If container does not contain an error, then assertion is triggered.
  Error& GetError() {}

  /// Returns reference to a value.
  /// \note If container does not contain a value, then assertion is triggered.
  T& GetValue() {}

  /// TODO:
  const T& operator->() const {}

  /// TODO:
  T& operator->() {}

  /// TODO:
  const T* operator*() const {}

  /// TODO:
  T* operator*() {}

  /// Throws exception if container holds an error, do nothing otherwise.
  void ThrowIfError() const {}

  /// Ignores containing value.
  void Ignore() const noexcept {
    // Do nothing.
  }

 private:
  explicit Result(Error&& error) {}

  explicit Result(T&& value) {}

  //
};

}  // namespace bicycle
