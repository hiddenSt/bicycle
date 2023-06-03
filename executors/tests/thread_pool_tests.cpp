#include <atomic>
#include <chrono>
#include <cstdint>
#include <thread>

#include <catch2/catch_all.hpp>

#include <bicycle/executors/task.hpp>
#include <bicycle/executors/thread_pool.hpp>

namespace bicycle::executors::tests {

using namespace std::chrono_literals;

struct TestTask : TaskBase {
  void Run() noexcept override { call_count.fetch_add(1); }

  std::atomic<std::uint8_t> call_count = 0;
};

TEST_CASE("") {
  ThreadPool pool;
  TestTask task_1;
  TestTask task_2;

  pool.Submit(&task_1);

  std::this_thread::sleep_for(10ms);
}

}  // namespace bicycle::executors::tests