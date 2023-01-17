#pragma once

#include <bicycle_export.hpp>

namespace bicycle::core {

/// Non-owning wrapper arround raw pointer.
template <typename T>
class BICYCLE_EXPORT ObserverPtr {
 public:
  /// Constructs observer with nullptr watched.
  ObserverPtr() = default;

  /// Constructs observer with \a watched object.
  explicit ObserverPtr(T* watched) noexcept : watched_(watched) {}

  ///
  ObserverPtr(const ObserverPtr& other) noexcept : watched_(other.watched_) {}

  ///
  ObserverPtr(ObserverPtr&& other) noexcept : watched_(other.watched_) { other.watched_ = nullptr; }

  ///
  ObserverPtr& operator=(const ObserverPtr& other) noexcept {
    watched_ = other.watched_;
    return *this;
  }

  ///
  ObserverPtr& operator=(ObserverPtr&& other) noexcept {
    watched_ = other.watched_;
    other.watched_ = nullptr;
    return *this;
  }

  ///
  T* operator->() noexcept { return watched_; }

  ///
  const T* operator->() const noexcept { return watched_; }

  ///
  T& operator*() { return *watched_; }

  ///
  const T& operator*() const noexcept { return *watched_; }

  /// Returns \c true if instance has no watched. (watched is \c nullptr), false otherwise.
  bool IsEmpty() const noexcept { return watched_ == nullptr; }

  T* Release() noexcept {
    T* released = watched_;
    watched_ = nullptr;

    return released;
  }

 private:
  T* watched_ = nullptr;
};

}  // namespace bicycle::core
