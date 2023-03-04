#pragma once

#include <bicycle/core/export.h>
#include <bicycle/core/contract.hpp>

#include <memory>
#include <system_error>
#include <type_traits>
#include <variant>

namespace bicycle::core {

/// \brief Container which represents the result of the operation call.
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
  [[nodiscard]] bool IsOk() const noexcept { return storage_.index() == 0; }

  /// Returns \a true if container contains an error, \a false otherwise.
  [[nodiscard]] bool HasError() const noexcept { return storage_.index() == 1; }

  /// Returns const reference to the error.
  /// \note If container does not contain an error, then assertion will be triggered.
  const Error& GetError() const noexcept {
    BICYCLE_EXPECTS(HasError());
    return std::get<Error>(storage_);
  }

  /// Returns const reference to a value.
  /// \note If container does not contain a value, then assertion will be triggered.
  const T& GetValue() const noexcept {
    BICYCLE_EXPECTS(IsOk());
    return std::get<T>(storage_);
  }

  /// Returns reference to an error.
  /// \note If container does not contain an error, then assertion is triggered.
  Error& GetError() noexcept {
    BICYCLE_EXPECTS(HasError());
    return std::get<Error>(storage_);
  }

  /// Returns reference to a value.
  /// \note If container does not contain a value, then assertion is triggered.
  T& GetValue() noexcept {
    BICYCLE_EXPECTS(IsOk());
    return std::get<T>(storage_);
  }

  /// TODO:
  const T* operator->() const noexcept { return GetValuePointer(); }

  /// TODO:
  T* operator->() noexcept { return GetValuePointer(); }

  /// TODO:
  const T* operator*() const noexcept { return GetValue(); }

  /// TODO:
  T* operator*() noexcept { return GetValue(); }

  /// Throws exception if container holds an error, do nothing otherwise.
  void ThrowIfError() const {
    if (HasError()) {
    }
  }

  /// \brief Ignores containing value.
  /// Does nothing with containing value.
  void Ignore() const noexcept {
    // Do nothing.
  }

 private:
  explicit Result(Error&& error) : storage_{std::in_place_type<Error>, std::move(error)} {}

  explicit Result(T&& value) : storage_{std::in_place_type<T>, std::move(value)} {}

  T* GetValuePointer() noexcept {
    BICYCLE_EXPECTS(IsOk());
    return static_cast<T*>(GetValue());
  }

  const T* GetValuePointer() const noexcept {
    BICYCLE_EXPECTS(IsOk());
    return static_cast<const T*>(GetValue());
  }

 private:
  std::variant<T, Error> storage_;
  //
};

}  // namespace bicycle::core
