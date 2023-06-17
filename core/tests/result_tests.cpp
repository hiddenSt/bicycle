#include <cstdint>
#include <string>
#include <system_error>

#include <catch2/catch_template_test_macros.hpp>

#include <bicycle/core/result.hpp>

namespace bicycle::core::tests {

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

TEMPLATE_TEST_CASE("Result assignment operators", "[result][assignment-op]", const char*, std::uint8_t) {
  SECTION("Copy-assignment operator test", "[copy]") {
    auto ok_result = Result<TestType>::Ok();
    auto failed_result = Result<TestType>::Fail();
    CHECK(ok_result.IsOk());
    CHECK(failed_result.HasError());
    ok_result = failed_result;
    CHECK(ok_result.HasError());
    CHECK(failed_result.HasError());
  }

  SECTION("Move-assignment operator test", "[move]") {
    auto ok_result = Result<TestType>::Ok();
    auto failed_result = Result<TestType>::Fail();
    failed_result = std::move(ok_result);
    CHECK(failed_result.IsOk());
    CHECK(ok_result.IsEmpty());
  }
}

}  // namespace bicycle::core::tests