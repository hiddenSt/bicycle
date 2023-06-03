#include <bicycle/allocator/mmap_allocation.hpp>

#include <sys/mman.h>
#include <unistd.h>

#include <bicycle/core/contracts.hpp>

namespace bicycle::allocator {

namespace detail {

std::size_t PagesToBytes(std::size_t count) {
  return count * MmapAllocation::PageSizeBytes();
}

}  // namespace detail

std::size_t MmapAllocation::PageSizeBytes() noexcept {
  static const std::size_t kPageSizeBytes = static_cast<std::size_t>(sysconf(_SC_PAGESIZE));
  return kPageSizeBytes;
}

MmapAllocation MmapAllocation::AllocatePages(std::size_t count) {
  std::size_t bytes_to_allocate = detail::PagesToBytes(count);
  void* allocation_result =
      ::mmap(nullptr, bytes_to_allocate, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  if (allocation_result == MAP_FAILED) {
    // TODO: add more precise message.
    BICYCLE_PANIC("Failed to allocate pages using ::mmap");
  }

  return {static_cast<std::uint8_t*>(allocation_result), bytes_to_allocate};
}

void MmapAllocation::ProtectPages(std::size_t offset, std::size_t count) noexcept {
  std::uint8_t* protected_region_start = page_bytes_.data() + detail::PagesToBytes(offset);
  int error_code = ::mprotect(static_cast<void*>(protected_region_start), count * PageSizeBytes(), PROT_NONE);
  BICYCLE_ENSURES(error_code != -1);
}

std::span<std::uint8_t> MmapAllocation::MutableView() noexcept { return page_bytes_; }

std::span<const std::uint8_t> MmapAllocation::View() const noexcept { return {page_bytes_.data(), page_bytes_.size()}; }

std::size_t MmapAllocation::SizePages() const noexcept { return SizeBytes() / PageSizeBytes(); }

std::size_t MmapAllocation::SizeBytes() const noexcept { return page_bytes_.size(); }

void MmapAllocation::Deallocate() noexcept {
  if (page_bytes_.empty()) {
    return;
  }

  int error_code = ::munmap(static_cast<void*>(page_bytes_.data()), SizeBytes());
  BICYCLE_ENSURES(error_code != -1);
}

MmapAllocation::MmapAllocation(std::uint8_t* start, std::size_t size_bytes) : page_bytes_(start, size_bytes) {}

}  // namespace bicycle::allocator
