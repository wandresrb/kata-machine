#pragma once

// A tiny dependency-free test harness.
//
//   TEST(my_test) {
//       expect_eq(actual, expected);
//   }
//
// Every TEST in the translation unit is registered automatically and run by
// the `main` defined at the bottom of this header (one test file == one
// executable). Failed expectations are reported with file:line and readable
// values; the process exits non-zero if anything failed.

#include <concepts>
#include <cstddef>
#include <exception>
#include <format>
#include <iostream>
#include <optional>
#include <ranges>
#include <source_location>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include <kata/types.hpp>

namespace kata::test {

// ---------------------------------------------------------------- printing --

template <class T>
std::string show(const T& value);

namespace detail {

template <class T>
concept StringLike = std::convertible_to<const T&, std::string_view>;

template <class T>
inline constexpr bool is_optional = false;
template <class T>
inline constexpr bool is_optional<std::optional<T>> = true;

}  // namespace detail

template <class T>
std::string show(const T& value) {
    using U = std::remove_cvref_t<T>;
    if constexpr (std::same_as<U, bool>) {
        return value ? "true" : "false";
    } else if constexpr (std::same_as<U, char>) {
        return std::format("'{}'", value);
    } else if constexpr (std::is_arithmetic_v<U>) {
        return std::format("{}", value);
    } else if constexpr (detail::StringLike<U>) {
        return std::format("{:?}", std::string_view{value});
    } else if constexpr (std::same_as<U, std::nullopt_t>) {
        return "nullopt";
    } else if constexpr (detail::is_optional<U>) {
        return value ? show(*value) : "nullopt";
    } else if constexpr (std::same_as<U, Point>) {
        return std::format("{{x: {}, y: {}}}", value.x, value.y);
    } else if constexpr (std::same_as<U, GraphEdge>) {
        return std::format("{{to: {}, weight: {}}}", value.to, value.weight);
    } else if constexpr (std::ranges::input_range<U>) {
        std::string out = "[";
        bool first = true;
        for (const auto& elem : value) {
            if (!first) out += ", ";
            first = false;
            out += show(elem);
        }
        return out + "]";
    } else {
        return "<unprintable>";
    }
}

// -------------------------------------------------------------- comparison --

namespace detail {

template <class T>
concept Integer = std::integral<T> && !std::same_as<T, bool> && !std::same_as<T, char>;

// Compares like `==`, but mixed signed/unsigned integers are compared by value
// (std::cmp_equal) so `expect_eq(list.length(), 2)` neither warns nor lies.
template <class A, class B>
bool equal(const A& a, const B& b) {
    if constexpr (Integer<A> && Integer<B>) {
        return std::cmp_equal(a, b);
    } else {
        return a == b;
    }
}

struct Test {
    std::string_view name;
    void (*body)();
};

inline std::vector<Test>& registry() {
    static std::vector<Test> tests;
    return tests;
}

inline int& failures() {
    static int count = 0;
    return count;
}

struct Registrar {
    Registrar(std::string_view name, void (*body)()) { registry().push_back({name, body}); }
};

}  // namespace detail

// ------------------------------------------------------------- assertions --

template <class Actual, class Expected>
bool expect_eq(const Actual& actual, const Expected& expected,
               std::source_location loc = std::source_location::current()) {
    if (detail::equal(actual, expected)) return true;
    ++detail::failures();
    std::cerr << std::format("{}:{}: expect_eq failed\n  actual:   {}\n  expected: {}\n",
                             loc.file_name(), loc.line(), show(actual), show(expected));
    return false;
}

inline bool expect(bool condition, std::string_view what = "condition",
                   std::source_location loc = std::source_location::current()) {
    if (condition) return true;
    ++detail::failures();
    std::cerr << std::format("{}:{}: expected {} to be true\n", loc.file_name(), loc.line(), what);
    return false;
}

// ------------------------------------------------------------------ runner --

inline int run_all() {
    int failed_tests = 0;
    for (const auto& [name, body] : detail::registry()) {
        std::cout << std::format("[ RUN  ] {}\n", name) << std::flush;
        const int before = detail::failures();
        try {
            body();
        } catch (const std::exception& e) {
            ++detail::failures();
            std::cerr << std::format("uncaught exception: {}\n", e.what());
        } catch (...) {
            ++detail::failures();
            std::cerr << "uncaught non-std exception\n";
        }
        const bool ok = detail::failures() == before;
        if (!ok) ++failed_tests;
        std::cout << std::format("[ {} ] {}\n", ok ? " OK " : "FAIL", name) << std::flush;
    }
    std::cout << std::format("{} test(s), {} failed\n", detail::registry().size(), failed_tests);
    return failed_tests == 0 ? 0 : 1;
}

}  // namespace kata::test

#define KATA_TEST_CONCAT_(a, b) a##b
#define KATA_TEST_CONCAT(a, b) KATA_TEST_CONCAT_(a, b)

#define TEST(name)                                                        \
    static void KATA_TEST_CONCAT(kata_test_, name)();                     \
    static const ::kata::test::detail::Registrar KATA_TEST_CONCAT(        \
        kata_test_registrar_, name){#name, &KATA_TEST_CONCAT(kata_test_, name)}; \
    static void KATA_TEST_CONCAT(kata_test_, name)()

#ifndef KATA_TEST_NO_MAIN
int main() { return ::kata::test::run_all(); }
#endif
