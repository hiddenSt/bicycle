#pragma once

#include <bicycle/core/export.h>
#include <bicycle/core/contracts.hpp>

#include <cstddef>
#include <memory>
#include <system_error>
#include <type_traits>

namespace bicycle::core {

namespace detail {

template <typename... Ts>
class AlignedStorage {
 public:
  // TODO: check if T is in Ts
  template <typename T, typename... Args>
  void Construct(Args&&... args) {
    auto ptr = reinterpret_cast<T*>(&storage_[0]);
    ::new (ptr) T(std::forward<Args>(args)...);
  }

  // TODO: check if T is in Ts
  template <typename T>
  void Destroy() {
    auto ptr = reinterpret_cast<T*>(&storage_[0]);
    ptr->~T();
  }

  template <typename T>
  T& GetAs() {
    auto ptr = reinterpret_cast<T*>(&storage_[0]);
    return *ptr;
  }

  template <typename T>
  const T& GetAs() const {
    auto ptr = reinterpret_cast<const T*>(&storage_[0]);
    return *ptr;
  }

 private:
  alignas(Ts...) std::byte storage_[std::max({sizeof(Ts)...})];
};

}  // namespace detail

/// \brief Container which represents the result of the operation call.
/// It either holds a value or an error. If the container holds the value, then it methods is TODO:
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

  /// Creates the result containing a value.
  template <typename... Args>
  static Result Ok(Args&&... args) {
    T value{std::forward<Args>(args)...};

    return Result{std::move(value)};
  }

  /// Constructs result from \a other. After call \a other remains as before call.
  Result(const Result& other) {
    CopyConstruct(other);
  }

  /// Moves \a other to this result. After call \a other is empty and can't be used.
  Result(Result&& other) noexcept {
    MoveConstruct(std::move(other));
  }

  /// Copies \a other to this. Previously holding state is properly destroyed.
  /// \a other remains the same as before call.
  Result& operator=(const Result& other) {
    Destroy();
    CopyConstruct(other);
    contains_ = other.contains_;
    return *this;
  }

  /// Moves \a other to this result. Previously holding state is properly destroyed.
  /// \a other becomes empty after call and can't be used.
  Result& operator=(Result&& other) noexcept {
    Destroy();
    MoveConstruct(std::move(other));
    return *this;
  }

  /// Returns \a true if the container contains a value, \a false otherwise.
  [[nodiscard]] bool IsOk() const noexcept { return contains_ == Contains::kValue; }

  /// Returns \a true if the container contains an error, \a false otherwise.
  [[nodiscard]] bool HasError() const noexcept { return contains_ != Contains::kValue; }

  [[nodiscard]] bool IsEmpty() const noexcept { return contains_ == Contains::kNothing; }

  /// Returns a const reference to the containing error.
  /// \note If the container does not contain an error, then the assertion will be triggered.
  const Error& GetError() const noexcept {
    BICYCLE_EXPECTS(HasError());
    return storage_.template GetAs<Error>();
  }

  /// Returns a const reference to the containing value.
  /// \note If the container does not contain a value, then the assertion will be triggered.
  const T& GetValue() const noexcept {
    BICYCLE_EXPECTS(IsOk());
    return storage_.template GetAs<T>();
  }

  /// Returns a reference to the containing error.
  /// \note If the container does not contain an error, then assertion is triggered.
  Error& GetError() noexcept {
    BICYCLE_EXPECTS(HasError());
    return storage_.template GetAs<Error>();
  }

  /// Returns a reference to the containing value.
  /// \note If container does not contain a value, then assertion is triggered.
  T& GetValue() noexcept {
    BICYCLE_EXPECTS(IsOk());
    return storage_.template GetAs<T>();
  }

  /// Returns a const pointer to the value.
  /// It is intended to be used as follows:
  const T* operator->() const noexcept { return GetPointerToValue(); }

  /// Returns a pointer to the value.
  /// It is intended to be uses as follows
  T* operator->() noexcept { return GetPointerToValue(); }

  /// Dereferences the  value.
  const T& operator*() const noexcept { return GetValue(); }

  /// Dereferences the value.
  T& operator*() noexcept { return GetValue(); }

  /// Throws an exception if result contains an error, returns a reference to the value otherwise.
  /// \note It is illegal to call this method after this result being moved to the other.
  T& ValueOrThrow() & {
    ThrowIfError();
    return GetValue();
  }

  const T& ValueOrThrow() const& {
    ThrowIfError();
    return GetValue();
  }

  T&& ValueOrThrow() && {
    ThrowIfError();
    return std::move(GetValue());
  }

  /// Throws an exception if the container holds an error, do nothing otherwise.
  void ThrowIfError() const {
    if (HasError()) {
      // TODO:
      throw std::system_error{};
    }
  }

  /// \brief Ignores a containing value or error.
  /// Does nothing with containing value.
  void Ignore() const noexcept {
    // Do nothing.
  }

  /// Same as \refitem IsOk().
  explicit operator bool() const noexcept { return IsOk(); }

 private:
  void CopyConstruct(const Result& other) {
    if (other.contains_ == Contains::kValue) {
      storage_.template Construct<T>(other.storage_.template GetAs<T>());
    } else if (other.contains_ == Contains::kError) {
      storage_.template Construct<Error>(other.storage_.template GetAs<Error>());
    }

    contains_ = other.contains_;
  }

  void MoveConstruct(Result&& other) {
    if (other.contains_ == Contains::kValue) {
      storage_.template Construct<T>(std::move(other.storage_.template GetAs<T>()));
    } else if (other.contains_ == Contains::kError) {
      storage_.template Construct<Error>(std::move(other.storage_.template GetAs<Error>()));
    }

    contains_ = other.contains_;
    other.contains_ = Contains::kNothing;
  }

  void Destroy() noexcept {
    if (contains_ == Contains::kValue) {
      storage_.template Destroy<T>();
    } else if (contains_ == Contains::kError) {
      storage_.template Destroy<T>();
    }

    contains_ = Contains::kNothing;
  }

  explicit Result(Error&& error) noexcept {
    storage_.template Construct<Error>(std::move(error));
    contains_ = Contains::kError;
  }

  explicit Result(T&& value) {
    storage_.template Construct<T>(std::move(value));
    contains_ = Contains::kValue;
  }

  T* GetPointerToValue() noexcept {
    BICYCLE_EXPECTS(IsOk());
    return static_cast<T*>(GetValue());
  }

  const T* GetPointerToValue() const noexcept {
    BICYCLE_EXPECTS(IsOk());
    return static_cast<const T*>(GetValue());
  }

 private:
  enum class Contains {
    kNothing,
    kValue,
    kError
  };

  detail::AlignedStorage<T, Error> storage_;
  Contains contains_;
};

/// Partial specialisation of Result which does not have to contain a value.
template <typename Error>
class [[nodiscard]] BICYCLE_EXPORT Result<void, Error> {
 public:
  template <typename... Args>
  static Result Fail(Args&&... args) {
    Error error{std::forward<Args>(args)...};
    return Result(std::move(error));
  }

  static Result Ok() { return Result{}; }

  [[nodiscard]] bool IsOk() const noexcept { return !has_error_; }

  [[nodiscard]] bool HasError() const noexcept { return has_error_; }

  const Error& GetError() const noexcept {
    BICYCLE_EXPECTS(HasError());
    return storage_.template GetAs<Error>();
  }

  Error& GetError() noexcept {
    BICYCLE_EXPECTS(HasError());
    return storage_.template GetAs<Error>();
  }

  void ThrowIfError() const {
    if (HasError()) {
      // TODO:
      throw std::system_error();
    }
  }

  void Ignore() const noexcept {
    // Does nothing.
  }

 private:
  Result() : has_error_{false} {}

  explicit Result(Error&& error) {
    storage_.Construct(std::move(error));
    has_error_ = true;
  }

 private:
  detail::AlignedStorage<Error> storage_;
  bool has_error_{false};
};

template <typename Error>
using Status = Result<void, Error>;

}  // namespace bicycle::core
