#pragma once

#include <source_location>
#include <string>

namespace bicycle::detail {

[[noreturn]] void Panic(std::source_location where, const std::string& error);

}  // namespace bicycle::detail

#if defined(__clang__) || defined(__GNUC__)
#define BICYCLE_LIKELY(x) __builtin_expect(!!(x), 1)
#define BICYCLE_UNLIKELY(x) __builtin_expect(!!(x), 0)
#endif

/// Causes program abnormal termination.
/// Before termination prints the current source location to stderr.
#define BICYCLE_PANIC(error)                                          \
  do {                                                                \
    ::bicycle::detail::Panic(std::source_location::current(), error); \
  } while (false)

#define BICYCLE_CONTRACT_CHECK(type, cond) \
  do {                                     \
    if (BICYCLE_UNLIKELY(!(cond))) {       \
      BICYCLE_PANIC(#type " failed.");     \
    }                                      \
  } while (false)

/// Validates \a cond. If validation fails causes abnormal program termination with current source location printed to
/// stderr.
#define BICYCLE_EXPECTS(cond) BICYCLE_CONTRACT_CHECK("Precondition", cond)

/// Validates \a cond. If validation fails.
#define BICYCLE_ENSURES(cond) BICYCLE_CONTRACT_CHECK("Postcondition", cond)

/// Indicates that code path is unreachable. If execution reaches this, then TODO:
#define BICYCLE_UNREACHABLE()                              \
  do {                                                     \
    BICYCLE_PANIC("Attempt to execute unreachable code."); \
  } while (false)
