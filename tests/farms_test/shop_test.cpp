#include "../../interactions/shop.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include "../../interactions/inventory.hpp"
#include <string>
inventory test_inventory;
Shop test_shop;
std::string expected;

TEST_CASE(" A Shop's welcome message works") {
    test_shop.link(&test_inventory, "Farmer");
    expected = "Hello, Farmer. Welcome to the shop!";
    REQUIRE( expected == test_shop.welcome());
}

TEST_CASE(" A Shop's menu options works") {
    expected = "\n1) Buy new Things\n2) Sell Produce/Seeds\n3) Return to Farm";
    REQUIRE( expected == test_shop.menu_options());
}

TEST_CASE(" A Shop's goodbye works") {
    expected = "Thanks for stopping bye!\n";
    REQUIRE( expected == test_shop.goodbye());
}


