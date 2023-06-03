#include <bicycle/core/contracts.hpp>

#include <cstdlib>
#include <iostream>
#include <mutex>

namespace bicycle::core::detail {

static std::mutex panic_stderr_lock = {};

[[noreturn]] void Panic(std::source_location where, const std::string& error) {
  std::lock_guard lock{panic_stderr_lock};
  std::cerr << "Panicked at '" << where.file_name() << "' " << where.function_name() << "[" << where.line()
            << "]:" << error << std::endl;
  std::abort();
}

}  // namespace bicycle::core::detail
