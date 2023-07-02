#pragma once

#include <bicycle/core/contracts.hpp>

namespace bicycle::core {

/// Non-owning wrapper around raw pointer.
template <typename T>
class ObserverPtr {
 public:
  /// Constructs observer with \c nullptr watched.
  ObserverPtr() noexcept = default;

  /// Constructs observer with \a watched object.
  explicit ObserverPtr(T* watched) noexcept : watched_(watched) {}

  /// Copies \a other watched pointer.
  ObserverPtr(const ObserverPtr& other) noexcept : watched_(other.watched_) {}

  /// Moves \a other watched pointer.
  /// After call \a other becomes empty, i. e. \a other watched pointer becomes \c nullptr.
  ObserverPtr(ObserverPtr&& other) noexcept : watched_(other.watched_) { other.watched_ = nullptr; }

  /// Copies \a other watched pointer.
  ObserverPtr& operator=(const ObserverPtr& other) noexcept {
    watched_ = other.watched_;
    return *this;
  }

  /// Moves \a other watched pointer.
  /// After call \a other becomes empty, i. e. \a other's watched pointer becomes \c nullptr.
  ObserverPtr& operator=(ObserverPtr&& other) noexcept {
    watched_ = other.watched_;
    other.watched_ = nullptr;
    return *this;
  }

  /// Destructor does nothing.
  ~ObserverPtr() = default;

  /// Returns a mutable pointer to the watched object.
  T* Get() noexcept { return watched_; }

  /// Returns an immutable pointer to the watched object.
  const T* Get() const noexcept { return watched_; }

  /// Returns a mutable pointer to the watched object.
  T* operator->() noexcept {
    BICYCLE_EXPECTS(!IsEmpty());
    return Get();
  }

  /// Returns an immutable pointer to the watched object.
  const T* operator->() const noexcept {
    BICYCLE_EXPECTS(!IsEmpty());
    return watched_;
  }

  /// Returns a mutable reference to the watched object.
  T& operator*() noexcept {
    BICYCLE_EXPECTS(!IsEmpty());
    return *watched_;
  }

  /// Returns an immutable reference to the watched object.
  const T& operator*() const noexcept {
    BICYCLE_EXPECTS(!IsEmpty());
    return *watched_;
  }

  /// Returns \c true if an object has no watched object, \c false otherwise.
  [[nodiscard]] bool IsEmpty() const noexcept { return watched_ == nullptr; }

  /// Releases the watched object and returns a mutable pointer to it.
  T* Release() noexcept {
    T* released = watched_;
    watched_ = nullptr;

    return released;
  }

  /// Returns \c true if the \a lhs watched object pointer is equal to the \a rhs watched object pointer,
  /// returns \c false otherwise.
  friend bool operator==(const ObserverPtr& lhs, const ObserverPtr& rhs) noexcept {
    return lhs.watched_ == rhs.watched_;
  }

  /// Returns \c true if the \a lhs watched pointer is not equal to the \a rhs watched pointer, \c false otherwise.
  friend bool operator!=(const ObserverPtr& lhs, const ObserverPtr& rhs) noexcept {
    return lhs.watched_ != rhs.watched_;
  }

  /// Returns \c true if the \a lhs watched pointer is less than the \a rhs watched pointer, \c false otherwise.
  friend bool operator<(const ObserverPtr& lhs, const ObserverPtr& rhs) noexcept { return lhs.watched_ < rhs.watched_; }

  /// Returns \c true if the \a lhs watched pointer is less or equal to the \a rhs watched pointer, \c false otherwise.
  friend bool operator<=(const ObserverPtr& lhs, const ObserverPtr& rhs) noexcept {
    return lhs.watched_ <= rhs.watched_;
  }

  /// Returns \c true if the \a lhs watched pointer is greater than the \a rhs watched pointer, \c false otherwise.
  friend bool operator>(const ObserverPtr& lhs, const ObserverPtr& rhs) noexcept { return lhs.watched_ > rhs.watched_; }

  /// Returns \c true if the \a lhs watched pointer is greater or equal to the \a rhs watched pointer, \c false otherwise.
  friend bool operator>=(const ObserverPtr& lhs, const ObserverPtr& rhs) noexcept {
    return lhs.watched_ >= rhs.watched_;
  }

 private:
  T* watched_ = nullptr;
};

}  // namespace bicycle::core
