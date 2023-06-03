#include <cstdint>
#include <string>
#include <system_error>

#include <catch2/catch_template_test_macros.hpp>

#include <bicycle/core/result.hpp>

namespace bicycle::core::tests {

class Leaker {
 public:
  Leaker() { memory_ = new std::uint8_t[10]; }

  ~Leaker() { delete[] memory_; }

 private:
  std::uint8_t* memory_ = nullptr;
};

TEMPLATE_TEST_CASE("Result constructors test", "[result][constructor]", const char*, std::uint8_t) {
  SECTION("Ok") {
    auto result = Result<TestType>::Ok();
    CHECK(result.IsOk());
    CHECK_FALSE(result.HasError());
    CHECK_NOTHROW(result.ThrowIfError());
    CHECK(result);
  }

  SECTION("Fail") {
    auto result = Result<TestType>::Fail();
    CHECK_FALSE(result.IsOk());
    CHECK(result.HasError());
    CHECK_THROWS_AS(result.ThrowIfError(), std::system_error);
  }
}

TEMPLATE_TEST_CASE("Result assignment operators test", "[result][assignment-op]", const char*, std::uint8_t) {
  SECTION("Copy-assignment operator test", "[copy]") {
    auto ok_result = Result<TestType>::Ok();
    auto failed_result = Result<TestType>::Fail();
    CHECK(ok_result.IsOk());
    CHECK(failed_result.HasError());
    ok_result = failed_result;
    CHECK(ok_result.HasError());
    CHECK(failed_result.HasError());
  }

  SECTION("Move-assignment operator test", "[move]") {}
}

TEMPLATE_TEST_CASE("Result with value test", "[result]", const char*, std::uint8_t) {}

TEMPLATE_TEST_CASE("Result with error test", "[result]", const char*, std::uint8_t) {}

TEST_CASE("Status constructor test", "[result][status][constructor]") {}

TEST_CASE("Status assignment operator", "[result][status][assignment-op]") {}

TEST_CASE("Status with error", "[result][status]") {}

TEST_CASE("Status", "[result][status]") {}

}  // namespace bicycle::core::tests