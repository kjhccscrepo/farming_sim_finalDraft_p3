#include "../../farm_stuff/farm.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>



#include "../../interactions/inventory.hpp"
#include "../../interactions/item.hpp"
#include "../../interactions/items/produce.hpp"
#include "../../interactions/items/seeds.hpp"
#include "../../plots/plant.hpp"
#include "../../plots/plot.hpp"
#include "../../plots/plants/carrot.hpp"
#include "../../plots/plants/melon.hpp"


TEST_CASE( "it can be initialized with a single plot" ) {
  Player player;
  Farm farm(1, 1);
  farm.link_Player(&player);
  REQUIRE( farm.row_capacity() == 1 );
  REQUIRE( farm.column_capacity() == 1 );
}
TEST_CASE( "it can be initialized as a 1x2 farm" ) {
  Player player;
  Farm farm(1, 2);
  farm.link_Player(&player);
  REQUIRE( farm.row_capacity() == 1 );
  REQUIRE( farm.column_capacity() == 2 );
}
TEST_CASE( "it can be initialized as a 2x1 farm" ) {
  Player player;
  Farm farm(2, 1);
  farm.link_Player(&player);
  REQUIRE( farm.row_capacity() == 2 );
  REQUIRE( farm.column_capacity() == 1 );
}
TEST_CASE( "it returns the symbol for a single soil plot" ) {
  Player player;
  Farm farm(1, 1);
  farm.link_Player(&player);
  REQUIRE( farm.get_symbol(0, 0) == "@" );
}
TEST_CASE( "it returns the symbols for a 1x2 farm" ) {
  Player player;
  Farm farm(1, 2);
  farm.link_Player(&player);
  REQUIRE( farm.get_symbol(0, 0) == "@" );
  REQUIRE( farm.get_symbol(0, 1) == "~" );
}
TEST_CASE( "it returns the symbols for a 2x1 farm" ) {
  Player player;
  Farm farm(2, 1);
  farm.link_Player(&player);
  REQUIRE( farm.get_symbol(0, 0) == "@" );
  REQUIRE( farm.get_symbol(1, 0) == "~" );
}
TEST_CASE( "it allows us to plant a carrot" ) {
  Player player;
  Farm farm(1, 2);
  farm.link_Player(&player);
  Carrot carrot;
  farm.plant(0, 1, &carrot);
  REQUIRE( farm.get_symbol(0, 1) == "x" );
}