#pragma once

namespace bicycle {

/// Non-owning wrapper arround raw pointer.
template <typename T>
class ObserverPtr {
 public:
  /// Constructs observer with nullptr watched.
  ObserverPtr() = default;

  /// Constructs observer with \a watched object.
  explicit ObserverPtr(T* watched) : watched_(ptr) noexcept {}

  ///
  ObserverPtr(const ObserverPtr& other) : watched_(other.watched_) noexcept {}

  ///
  ObserverPtr(ObserverPtr&& other) : watched_(other.watched_) noexcept { other.watched_ = nullptr; }

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
  const T& operator*() { return *watched_; }

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

}  // namespace bicycle
