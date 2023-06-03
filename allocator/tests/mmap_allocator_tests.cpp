#include <catch2/catch_all.hpp>

#include <bicycle/allocator/mmap_allocation.hpp>

namespace bicycle::allocator::tests {

TEST_CASE("Allocator", "[allocator][mmap_allocation]") {
  SECTION("Allocating 1 page") {
    MmapAllocation allocation = MmapAllocation::AllocatePages(1);
    CHECK(allocation.SizePages() == 1);
    CHECK(allocation.SizeBytes() == MmapAllocation::PageSizeBytes());
    allocation.Deallocate();
  }

  SECTION("Allocation 2 pages") {
    MmapAllocation allocation = MmapAllocation::AllocatePages(2);
    CHECK(allocation.SizePages() == 2);
    CHECK(allocation.SizeBytes() == MmapAllocation::PageSizeBytes() * 2);
    allocation.Deallocate();
  }

  SECTION("Protecting pages") {
    MmapAllocation allocation = MmapAllocation::AllocatePages(1);
    // allocation.ProtectPages(0, 1);
    auto memory = allocation.MutableView();
    new (memory.data()) int(100);
  }
}

}  // namespace bicycle::allocator::tests