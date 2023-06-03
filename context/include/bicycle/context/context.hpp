#pragma once

#include <cstdint>
#include <span>

#include <bicycle/context/trampoline.hpp>

namespace bicycle::context {

struct MachineContext {
  void* rsp;

  void Setup(std::span<std::uint8_t> stack, Trampoline* trampoline);

  void SwitchTo(MachineContext& target);
};

}  // namespace bicycle::context