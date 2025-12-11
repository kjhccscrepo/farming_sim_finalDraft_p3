#include "../../farm_stuff/farmland.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include "../../interactions/inventory.hpp"
#include "../../plots/plot.hpp"
#include "../../plots/plants/carrot.hpp"
#include "../../random/test_random.hpp"

test_random random_test;
bool hard = false;

TEST_CASE( "it can be initialized with a single plot" ) {
  Player player;
  Farmland farm(1, 1, &player, &random_test, &hard);
  REQUIRE( farm.row_capacity() == 1 );
  REQUIRE( farm.column_capacity() == 1 );
}
TEST_CASE( "it can be initialized as a 1x2 farm" ) {
  Player player;
  Farmland farm(1, 2, &player, &random_test, &hard);
  REQUIRE( farm.row_capacity() == 1 );
  REQUIRE( farm.column_capacity() == 2 );
}
TEST_CASE( "it can be initialized as a 2x1 farm" ) {
  Player player;
  Farmland farm(2, 1, &player, &random_test, &hard);
  REQUIRE( farm.row_capacity() == 2 );
  REQUIRE( farm.column_capacity() == 1 );
}
TEST_CASE( "it returns the symbol for a single soil plot" ) {
  Player player;
  Farmland farm(1, 1, &player, &random_test, &hard);
  REQUIRE( farm.get_symbol(0, 0) == "@" );
}
TEST_CASE( "it returns the symbols for a 1x2 farm" ) {
  Player player;
  Farmland farm(1, 2, &player, &random_test, &hard);
  REQUIRE( farm.get_symbol(0, 0) == "~" );
  REQUIRE( farm.get_symbol(0, 1) == "@" );
}
TEST_CASE( "it returns the symbols for a 2x1 farm" ) {
  Player player;
  Farmland farm(2, 1, &player, &random_test, &hard);
  REQUIRE( farm.get_symbol(0, 0) == "@" );
  REQUIRE( farm.get_symbol(1, 0) == "~" );
}
TEST_CASE( "it allows us to plant a carrot" ) {
  Player player;
  Farmland farm(1, 2, &player, &random_test, &hard);
  Carrot carrot;
  farm.plant(0, 1, &carrot);
  farm.move_player_up();
  REQUIRE( farm.get_symbol(0, 0) == "@" );
  REQUIRE( farm.get_symbol(0, 1) == "x" );
}