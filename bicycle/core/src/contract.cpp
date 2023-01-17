#include <bicycle/contract.hpp>
#include <cstdlib>
#include <iostream>

namespace bicycle::core::detail {

[[noreturn]] void Panic(std::source_location where, const std::string& error) {
  std::cerr << error << " (file=" << where.file_name() << ", function=" << where.function_name()
            << ", line=" << where.line() << ", column=" << where.column() << ")." << std::endl;
  std::abort();
}

}  // namespace bicycle::core::detail
