#include "../../interactions/inventory.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include "../../plots/plant.hpp"
#include "../../interactions/item.hpp"
#include "../../interactions/items/produce.hpp"
#include "../../interactions/items/seeds.hpp"
#include "../../plots/plants/carrot.hpp"


TEST_CASE( "an inventory can have an item put in it" ) {
    inventory inventory_test;
    REQUIRE( inventory_test.how_many_types_of_things() == 0);
    // empty inventory
    Carrot carrot;
    produce carrot_produce(&carrot);
    inventory_test.add_item(&carrot_produce);
    REQUIRE( inventory_test.how_many_types_of_things() == 1);
}
TEST_CASE( "an inventory can check if an item is plantable" ) {
    inventory inventory_test;
    Carrot carrot;
    seeds carrot_seeds(&carrot);
    produce carrot_produce(&carrot);
    inventory_test.add_item(&carrot_produce);
    REQUIRE( inventory_test.is_first_item_plantable() == false);
    inventory_test.add_item(&carrot_seeds);
    REQUIRE( inventory_test.is_X_item_plantable(1) == true);
    inventory_test.move_item_to_front(1);
    REQUIRE( inventory_test.is_first_item_plantable() == true);
    REQUIRE( inventory_test.is_X_item_plantable(1) == false);
}
TEST_CASE( "an inventory can check the name of the item" ) {
    inventory inventory_test;
    Carrot carrot;
    seeds carrot_seeds(&carrot);
    produce carrot_produce(&carrot);
    inventory_test.add_item(&carrot_produce);
    REQUIRE( inventory_test.first_name() == "Carrot(s)");
    inventory_test.add_item(&carrot_seeds);
    inventory_test.move_item_to_front(1);
    REQUIRE( inventory_test.first_name() == "Carrot seeds");
}
TEST_CASE( "an inventory can check if it contains an item" ) {
    inventory inventory_test;
    Carrot carrot;
    seeds carrot_seeds(&carrot);
    produce carrot_produce(&carrot);
    inventory_test.add_item(&carrot_produce);
    REQUIRE( inventory_test.has(&carrot_produce) == 0);
    REQUIRE( inventory_test.has(&carrot_seeds) == -1);
    inventory_test.add_item(&carrot_seeds);
    REQUIRE( inventory_test.has(&carrot_seeds) == 1);
}
TEST_CASE( "an inventory can modify the quantity of an item" ) {
    inventory inventory_test;
    Carrot carrot;
    produce carrot_produce(&carrot);
    seeds carrot_seeds(&carrot);
    REQUIRE( inventory_test.can_remove(&carrot_produce) == false);
    inventory_test.add_item(&carrot_produce);
    REQUIRE( inventory_test.can_remove(&carrot_produce) == true);
    inventory_test.remove_item(&carrot_produce);
    inventory_test.remove_item(&carrot_produce);
    REQUIRE( inventory_test.can_remove(&carrot_produce) == false);
    inventory_test.add_item(&carrot_seeds);
    REQUIRE( inventory_test.how_many_types_of_things() == 2);
    inventory_test.add_item_X_times(&carrot_seeds, 7);
    REQUIRE( inventory_test.can_remove(&carrot_seeds) == true);
    inventory_test.remove_item(&carrot_seeds);
    inventory_test.remove_item(&carrot_seeds);
    inventory_test.remove_item(&carrot_seeds);
    inventory_test.remove_item(&carrot_seeds);
    inventory_test.remove_item(&carrot_seeds);
    inventory_test.remove_item(&carrot_seeds);
    inventory_test.remove_item(&carrot_seeds);
    inventory_test.remove_item(&carrot_seeds);
    REQUIRE( inventory_test.can_remove(&carrot_seeds) == false);
}
TEST_CASE( "an inventory returns an expected string" ) {
    inventory inventory_test;
    Carrot carrot;
    produce carrot_produce(&carrot);
    seeds carrot_seeds(&carrot);
    inventory_test.add_item(&carrot_produce);
    inventory_test.add_item(&carrot_seeds);
    inventory_test.add_item_X_times(&carrot_produce, 2);
    inventory_test.add_item_X_times(&carrot_seeds, 7);
    std::stringstream expected;
    expected        << "Carrot(s), \t3x\n"
                    << "Carrot seeds, \t8x\n";
    REQUIRE( inventory_test.inventory_stream().str() == expected.str());
}