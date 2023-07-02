#pragma once

#include <source_location>
#include <string>

#include <bicycle/core/export.h>

namespace bicycle::core::detail {

/// \internal
[[noreturn]] void BICYCLE_EXPORT Panic(std::source_location where, const std::string& error);

}  // namespace bicycle::core::detail

#if defined(__clang__) || defined(__GNUC__)
/// \internal
#define BICYCLE_LIKELY(x) __builtin_expect(!!(x), 1)

/// \internal
#define BICYCLE_UNLIKELY(x) __builtin_expect(!!(x), 0)
#endif

/// \brief Causes program abnormal termination.
/// Before the termination prints the current source location to \a stderr.
#define BICYCLE_PANIC(error)                                                \
  do {                                                                      \
    ::bicycle::core::detail::Panic(std::source_location::current(), error); \
  } while (false)

/// \internal
#define BICYCLE_CONTRACT_CHECK(type, cond) \
  do {                                     \
    if (BICYCLE_UNLIKELY(!(cond))) {       \
      BICYCLE_PANIC(#type " failed.");     \
    }                                      \
  } while (false)

/// Validates \a cond. If validation fails causes abnormal program termination
/// with the current source location printed to \a stderr .
#define BICYCLE_EXPECTS(cond) BICYCLE_CONTRACT_CHECK("Precondition", cond)

/// Validates \a cond. If validation fails causes abnormal termination
/// with current source location printed to \a stderr .
#define BICYCLE_ENSURES(cond) BICYCLE_CONTRACT_CHECK("Postcondition", cond)

/// Indicates that code path is unreachable. Execution reached this causes
/// abnormal process termination with the current source location printed to \a stderr .
#define BICYCLE_UNREACHABLE()                              \
  do {                                                     \
    BICYCLE_PANIC("Attempt to execute unreachable code."); \
  } while (false)