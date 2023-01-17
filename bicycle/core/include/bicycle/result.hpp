#pragma once

#include <bicycle/contract.hpp>
#include <bicycle_export.hpp>

#include <memory>
#include <system_error>
#include <type_traits>

namespace bicycle::core {

/// \brief Container which represents the result of operation call.
/// It either holds a value or an error. If container holds the value, then it methods is TODO:
/// Inspired by [this article]()
template <typename T, typename Error = std::error_code>
class [[nodiscard]] BICYCLE_EXPORT Result {
 public:
  static_assert(!std::is_reference_v<T>, "T can not be a reference");
  static_assert(!std::is_reference_v<Error>, "Error can not be a reference");

  /// Creates the result containing an error.
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

  /// Returns \a true if container contains a value, \a false otherwise.
  [[nodiscard]] bool IsOk() const noexcept {}

  /// Returns \a true if container contains an error, \a false otherwise.
  [[nodiscard]] bool HasError() const noexcept {}

  /// Returns const reference to the error.
  /// \note If container does not contain an error, then assertion will be triggered.
  const Error& GetError() const { BICYCLE_EXPECTS(HasError()); }

  /// Returns const reference to a value.
  /// \note If container does not contain a value, then assertion will be triggered.
  const T& GetValue() const { BICYCLE_EXPECTS(IsOk()); }

  /// Returns reference to an error.
  /// \note If container does not contain an error, then assertion is triggered.
  Error& GetError() { BICYCLE_EXPECTS(HasError()); }

  /// Returns reference to a value.
  /// \note If container does not contain a value, then assertion is triggered.
  T& GetValue() { BICYCLE_EXPECTS(IsOk()); }

  /// TODO:
  const T& operator->() const { BICYCLE_EXPECTS(IsOk()); }

  /// TODO:
  T& operator->() { BICYCLE_EXPECTS(IsOk()); }

  /// TODO:
  const T* operator*() const { BICYCLE_EXPECTS(IsOk()); }

  /// TODO:
  T* operator*() { BICYCLE_EXPECTS(IsOk()); }

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

}  // namespace bicycle::core
