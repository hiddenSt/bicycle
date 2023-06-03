#include <cstdint>
#include <string>
#include <utility>

#include <catch2/catch_template_test_macros.hpp>

#include <bicycle/core/observer_ptr.hpp>

namespace bicycle::core::tests {

TEMPLATE_TEST_CASE("ObserverPtr constructors", "[ObserverPtr]", std::uint8_t, char, const char,
                   (std::pair<std::uint8_t, char>)) {
  SECTION("Default constructor") {
    ObserverPtr<TestType> observer;
    REQUIRE(observer.IsEmpty());
    CHECK(observer.Get() == nullptr);
  }

  SECTION("Pointer constructor") {
    TestType watched{};
    ObserverPtr<TestType> observer(&watched);
    REQUIRE_FALSE(observer.IsEmpty());
    CHECK(observer.Get() == &watched);
  }

  SECTION("Copy constructor") {
    TestType watched{};
    ObserverPtr<TestType> observer_1(&watched);
    REQUIRE_FALSE(observer_1.IsEmpty());
    ObserverPtr<TestType> observer_2{observer_1};
    CHECK_FALSE(observer_1.IsEmpty());
    CHECK_FALSE(observer_2.IsEmpty());
    CHECK(observer_1.Get() == observer_2.Get());
    CHECK(observer_1 == observer_2);
  }

  SECTION("Move constructor") {
    TestType watched{};
    ObserverPtr<TestType> observer_1(&watched);
    REQUIRE_FALSE(observer_1.IsEmpty());
    ObserverPtr<TestType> observer_2(std::move(observer_1));
    CHECK(observer_1.IsEmpty());
    CHECK_FALSE(observer_2.IsEmpty());
    CHECK(observer_2.Get() == &watched);
    CHECK(observer_1.Get() == nullptr);
  }
}

TEMPLATE_TEST_CASE("ObserverPtr assignment operators", "[ObserverPtr]", std::uint8_t, char, const char,
                   (std::pair<std::uint8_t, char>)) {
  SECTION("Copy assignment operator") {
    TestType watched{};
    ObserverPtr<TestType> observer_1(&watched);
    ObserverPtr<TestType> observer_2;
    REQUIRE_FALSE(observer_1.IsEmpty());
    REQUIRE(observer_2.IsEmpty());
    observer_2 = observer_1;
    CHECK_FALSE(observer_1.IsEmpty());
    CHECK_FALSE(observer_2.IsEmpty());
    CHECK(observer_1.Get() == observer_2.Get());
    CHECK(observer_1 == observer_2);
  }

  SECTION("Move assignment operator") {
    TestType watched{};
    ObserverPtr<TestType> observer_1(&watched);
    ObserverPtr<TestType> observer_2;
    REQUIRE_FALSE(observer_1.IsEmpty());
    REQUIRE(observer_2.IsEmpty());
    observer_2 = std::move(observer_1);
    CHECK(observer_1.IsEmpty());
    CHECK_FALSE(observer_2.IsEmpty());
    CHECK(observer_2.Get() == &watched);
    CHECK(observer_1.Get() == nullptr);
  }
}

TEMPLATE_TEST_CASE("Comparison operators", "ObserverPtr", std::uint8_t, std::string, const char, char, std::uint8_t*) {
  SECTION("equal") {
    TestType watched{};
    ObserverPtr lhs{&watched};
    ObserverPtr rhs{&watched};

    REQUIRE(lhs == rhs);
    REQUIRE_FALSE(lhs != rhs);
  }

  SECTION("not equal") {
    TestType watched_1{};
    TestType watched_2{};
    ObserverPtr lhs{&watched_1};
    ObserverPtr rhs{&watched_2};

    REQUIRE(lhs != rhs);
    REQUIRE_FALSE(lhs == rhs);
  }
}

TEMPLATE_TEST_CASE("Release", "ObserverPtr", std::uint8_t, std::string, const char, char, std::uint8_t*) {
  TestType watched{};
  ObserverPtr observer{&watched};
  REQUIRE_FALSE(observer.IsEmpty());
  REQUIRE(observer.Get() == &watched);
  observer.Release();
  CHECK(observer.IsEmpty());
  CHECK(observer.Get() == nullptr);
}

}  // namespace bicycle::core::tests
