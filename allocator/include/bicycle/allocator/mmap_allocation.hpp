#pragma once

#include <cstdint>
#include <span>
#include <span>

#include <bicycle/allocator/export.h>

namespace bicycle::allocator {

/// Easy to use wrapper around ::mmap/::munmap system calls.
/// Allows to allocate private anonymous virtual memory pages.
class BICYCLE_EXPORT MmapAllocation {
 public:
  /// Returns the system page size in bytes.
  static std::size_t PageSizeBytes() noexcept;

  /// Allocates contiguous region of \a count pages via ::mmap.
  static MmapAllocation AllocatePages(std::size_t count);

  /// Protects \a count pages at \a offset.
  void ProtectPages(std::size_t offset, std::size_t count) noexcept;

  /// Returns mutable view of pages.
  std::span<std::uint8_t> MutableView() noexcept;

  /// Returns immutable view of pages.
  std::span<const std::uint8_t> View() const noexcept;

  /// Returns the size of the region in pages.
  std::size_t SizePages() const noexcept;

  /// Returns the size of the region in bytes.
  std::size_t SizeBytes() const noexcept;

  /// Deallocates pages via ::munmap.
  void Deallocate() noexcept;

 private:
  MmapAllocation(std::uint8_t* start, std::size_t size_bytes);

  std::span<std::uint8_t> page_bytes_;
};

}  // namespace bicycle::allocator
