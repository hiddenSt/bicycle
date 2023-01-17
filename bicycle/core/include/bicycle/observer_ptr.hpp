#pragma once

#include <bicycle_export.hpp>
#include <bicycle/contract.hpp>

namespace bicycle::core {

/// Non-owning wrapper around raw pointer.
template <typename T>
class BICYCLE_EXPORT ObserverPtr {
 public:
  /// Constructs observer with nullptr watched.
  ObserverPtr() noexcept = default;

  /// Constructs observer with \a watched object.
  explicit ObserverPtr(T* watched) noexcept : watched_(watched) {}

  /// Copy constructor.
  ObserverPtr(const ObserverPtr& other) noexcept : watched_(other.watched_) {}

  /// Move constructor. After call, \a other becomes empty.
  ObserverPtr(ObserverPtr&& other) noexcept : watched_(other.watched_) { other.watched_ = nullptr; }

  /// Copy assignment operator.
  ObserverPtr& operator=(const ObserverPtr& other) noexcept {
    watched_ = other.watched_;
    return *this;
  }

  /// Move assignment operator. After call \a other becomes empty.
  ObserverPtr& operator=(ObserverPtr&& other) noexcept {
    watched_ = other.watched_;
    other.watched_ = nullptr;
    return *this;
  }
  
  /// Destructor does nothing.
  ~ObserverPtr() = default;
  
  /// Returns a mutable pointer to the wrapped object.
  T* Get() noexcept {
    return watched_;
  }
  
  /// Returns an immutable pointer to the wrapped object.
  const T* Get() const noexcept {
    return watched_;
  }

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

  /// Returns \a true if object has no watched entity, \a false otherwise.
  [[nodiscard]] bool IsEmpty() const noexcept { return watched_ == nullptr; }
  
  /// Releases the watched object and returns mutable pointer to it.
  T* Release() noexcept {
    T* released = watched_;
    watched_ = nullptr;

    return released;
  }
  
  /// Returns \a true if the \a lhs watched object pointer is equal to the \a rhs watched object pointer, \a false otherwise.
  friend bool operator==(const ObserverPtr& lhs, const ObserverPtr& rhs) noexcept { return lhs.watched_ == rhs.watched_; }
  
  /// Returns \a true if the \a lhs watched object pointer is not equal to the  \a rhs watched object pointer, \a false otherwise.
  friend bool operator==(const ObserverPtr& lhs, const ObserverPtr& rhs) noexcept { return lhs.watched_ != rhs.watched_; }

 private:
  T* watched_ = nullptr;
};

}  // namespace bicycle::core
