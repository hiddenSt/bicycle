#include <bicycle/context/context.hpp>

#include "detail/switch_machine_context.hpp"

namespace bicycle::context {

void MachineContext::Setup(std::span<std::uint8_t> stack, Trampoline* trampoline) {

}

void MachineContext::SwitchTo(MachineContext& target) {
  SwitchMachineContext(rsp, target.rsp);
}

}  // namespace bicycle::context