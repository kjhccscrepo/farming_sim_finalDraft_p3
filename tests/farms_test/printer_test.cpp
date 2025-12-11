#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include "../../farm_stuff/farm_printer.hpp"
#include "../../farm_stuff/game_printer.hpp"
#include "../../interactions/inventory.hpp"
#include "../../interactions/items/seeds.hpp"
#include "../../interactions/items/produce.hpp"
#include "../../plots/plant.hpp"
#include "../../plots/plants/carrot.hpp"
#include "../../plots/plants/melon.hpp"
#include "../../plots/soil.hpp"
#include "../../entities/player.hpp"
#include "../../random/test_random.hpp"

test_random TestRand;
bool hard = false;

TEST_CASE( "it pretty prints a single plot of land" ) {
    Player p("P");
    Farmland farm(1, 1, &p, &TestRand, &hard);
    FarmPrinter printer(&farm);
    std::stringstream expected;
  expected  << "/ / / \n"
            << "/ P / \n"
            << "/ / / \n";
  REQUIRE( printer.prettyPrint().str() == expected.str() );
}

TEST_CASE( "it pretty prints a 1x2 farm" ) {
  Player player("P");
  Farmland farm(1, 2, &player, &TestRand, &hard);
  FarmPrinter printer(&farm);
  std::stringstream expected;
  expected  << "/ / / \n"
            << "/ ~ / \n"
            << "/ P / \n"
            << "/ / / \n";
  REQUIRE( printer.prettyPrint().str() == expected.str() );
}
TEST_CASE( "it pretty prints a 2x1 farm" ) {
  Player player("P");
  Farmland farm(2, 1, &player, &TestRand, &hard);
  FarmPrinter printer(&farm);
  std::stringstream expected;
  expected  << "/ / / / \n"
            << "/ P ~ / \n"
            << "/ / / / \n";
  REQUIRE( printer.prettyPrint().str() == expected.str() );
}
TEST_CASE( "it pretty prints a 2x2 farm" ) {
    Player player("P");
    Farmland farm(2, 2, &player, &TestRand, &hard);
    FarmPrinter printer(&farm);
    std::stringstream expected;
    expected  << "/ / / / \n"
              << "/ ~ ~ / \n"
              << "/ P ~ / \n"
              << "/ / / / \n";
    REQUIRE( printer.prettyPrint().str() == expected.str() );
}
TEST_CASE( "player moves" ) {
    Player player("P");
    Farmland farm(3, 3, &player, &TestRand, &hard);
    FarmPrinter printer(&farm);
    farm.move_player_up();
    farm.move_player_up();
    farm.move_player_left();
    farm.move_player_left();
    std::stringstream expected;
    expected  << "/ / / / / \n"
              << "/ P ~ ~ / \n"
              << "/ ~ ~ ~ / \n"
              << "/ ~ ~ ~ / \n"
              << "/ / / / / \n";
    REQUIRE( printer.prettyPrint().str() == expected.str() );
    player.move_right();
    expected.str("");
    expected.clear();
    expected    << "/ / / / / \n"
                << "/ ~ P ~ / \n"
                << "/ ~ ~ ~ / \n"
                << "/ ~ ~ ~ / \n"
                << "/ / / / / \n";
    REQUIRE( printer.prettyPrint().str() == expected.str() );
    player.move_left();
    player.move_down();
    player.move_down();
    expected.str("");
    expected.clear();
    expected    << "/ / / / / \n"
                << "/ ~ ~ ~ / \n"
                << "/ ~ ~ ~ / \n"
                << "/ P ~ ~ / \n"
                << "/ / / / / \n";
    REQUIRE( printer.prettyPrint().str() == expected.str() );
    player.move_right();
    player.move_up();
    expected.str("");
    expected.clear();
    expected    << "/ / / / / \n"
                << "/ ~ ~ ~ / \n"
                << "/ ~ P ~ / \n"
                << "/ ~ ~ ~ / \n"
                << "/ / / / / \n";
    REQUIRE( printer.prettyPrint().str() == expected.str() );
    player.move_left();
    player.move_up();
    expected.str("");
    expected.clear();
    expected    << "/ / / / / \n"
                << "/ P ~ ~ / \n"
                << "/ ~ ~ ~ / \n"
                << "/ ~ ~ ~ / \n"
                << "/ / / / / \n";
    REQUIRE( printer.prettyPrint().str() == expected.str() );
    player.move_right();
    player.move_right();
    player.move_down();
    player.move_down();
    expected.str("");
    expected.clear();
    expected    << "/ / / / / \n"
                << "/ ~ ~ ~ / \n"
                << "/ ~ ~ ~ / \n"
                << "/ ~ ~ P / \n"
                << "/ / / / / \n";
    REQUIRE( printer.prettyPrint().str() == expected.str() );
}
TEST_CASE( "player plants a carrot" ) {
    Player player("P");
    inventory inventory;
    Farmland farm(3, 3, &player, &TestRand, &hard);
    farm.move_player_up();
    farm.move_player_up();
    farm.move_player_left();
    farm.move_player_left();
    FarmPrinter printer(&farm);
    Carrot carrot;
    seeds seed_carrot(&carrot);
    produce produce_carrot(&carrot);
    carrot.link_this_class(&seed_carrot, &produce_carrot);
    inventory.add_item(&seed_carrot);
    std::stringstream expected;
    expected  << "/ / / / / \n"
              << "/ P ~ ~ / \n"
              << "/ ~ ~ ~ / \n"
              << "/ ~ ~ ~ / \n"
              << "/ / / / / \n";
    REQUIRE( printer.prettyPrint().str() == expected.str() );
    farm.plant(player.getX(), player.getY(), &carrot);
    player.move_right();
    player.move_down();
    expected.str("");
    expected.clear();
    expected    << "/ / / / / \n"
                << "/ x ~ ~ / \n"
                << "/ ~ P ~ / \n"
                << "/ ~ ~ ~ / \n"
                << "/ / / / / \n";
    REQUIRE( printer.prettyPrint().str() == expected.str() );
}
TEST_CASE( "player grows a carrot" ) {
    Player player("P");
    inventory inventory;
    Farmland farm(3, 3, &player, &TestRand, &hard);
    FarmPrinter printer(&farm);
    Carrot carrot;
    seeds seed_carrot(&carrot);
    produce produce_carrot(&carrot);
    carrot.link_this_class(&seed_carrot, &produce_carrot);
    inventory.add_item(&seed_carrot);
    farm.move_player_up();
    farm.move_player_up();
    farm.move_player_up();
    farm.move_player_left();
    REQUIRE( farm.get_symbol(0, 0) == player.getAvatar());
    farm.plant(player.getX(), player.getY(), &carrot);
    player.move_right();
    player.move_down();
    std::stringstream expected;
    expected.str("");
    expected.clear();
    expected    << "/ / / / / \n"
                << "/ x ~ ~ / \n"
                << "/ ~ P ~ / \n"
                << "/ ~ ~ ~ / \n"
                << "/ / / / / \n";
    REQUIRE( printer.prettyPrint().str() == expected.str() );
    farm.end_day();
    expected.str("");
    expected.clear();
    expected    << "/ / / / / \n"
                << "/ w ~ ~ / \n"
                << "/ ~ P ~ / \n"
                << "/ ~ ~ ~ / \n"
                << "/ / / / / \n";
    REQUIRE( printer.prettyPrint().str() == expected.str() );
    farm.end_day();
    expected.str("");
    expected.clear();
    expected    << "/ / / / / \n"
                << "/ W ~ ~ / \n"
                << "/ ~ P ~ / \n"
                << "/ ~ ~ ~ / \n"
                << "/ / / / / \n";
    REQUIRE( printer.prettyPrint().str() == expected.str() );
}
TEST_CASE( "game printer produces the legend." ) {
    inventory inventory_test;
    Carrot carrot;
    produce carrot_produce(&carrot);
    seeds carrot_seeds(&carrot);
    carrot.link_this_class(&carrot_seeds, &carrot_produce);
    inventory_test.add_item(&carrot_seeds);
    Player player;
    Farmland farm(5, 5, &player, &TestRand, &hard);
    FarmPrinter printer_farm(&farm);
    GamePrinter printer(&printer_farm, &inventory_test);
    std::stringstream expected;
    expected     << "CONTROLS\n"
                 << "w:\tmove up\n"
                 << "s:\tmove down\n"
                 << "a:\tmove left\n"
                 << "d:\tmove right\n"
                 << "i:\tview inventory\n"
                 << "p:\tplant selected seed\n"
                 << "o:\tchange selected seed\n"
                 << "h:\tharvest grown crop\n"
                 << "e:\tend the day\n"
                 << "t:\twater the selected plot\n"
                 << "m:\tgo to the shop\n"
                 << "q:\tquit the game\n"
                 << "r:\treturn to the game\n";
    printer.generate_legend();
    REQUIRE(printer.prettyPrint_Legend() == expected.str());
}
TEST_CASE( "game printer produces the inventory." ) {
    inventory inventory_test;
    Carrot carrot;
    produce carrot_produce(&carrot);
    seeds carrot_seeds(&carrot);
    carrot.link_this_class(&carrot_seeds, &carrot_produce);
    inventory_test.add_item_X_times(&carrot_seeds, 9);
    inventory_test.add_item_X_times(&carrot_produce, 3);
    Melon melon;
    produce melon_produce(&melon);
    seeds melon_seeds(&melon);
    melon.link_this_class(&melon_seeds, &melon_produce);
    inventory_test.add_item_X_times(&melon_seeds, 22);
    inventory_test.add_item_X_times(&melon_produce, 30);
    Player player;
    Farmland farm(5, 5, &player, &TestRand, &hard);
    FarmPrinter printer_farm(&farm);
    GamePrinter printer(&printer_farm, &inventory_test);
    std::stringstream expected;
    expected     << "INVENTORY\n"
                 << "1:\tCarrot seeds, \t9x\n"
                 << "2:\tCarrot(s), \t3x\n"
                 << "3:\tMelon seeds, \t22x\n"
                 << "4:\tMelon(s), \t30x\n"
                 << "r:\treturn to the game\n";
    printer.generate_inventory();
    REQUIRE(printer.prettyPrint_Inventory() == expected.str());
}