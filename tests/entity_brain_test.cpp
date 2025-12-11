//
// Created by kistj on 12/11/2025.
//
#include "../logic/entity_brain.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include "../interactions/inventory.hpp"
#include "../random/test_random.hpp"
#include "../farm_stuff/farmland.hpp"
#include "../entities/bunny.hpp"

TEST_CASE( "An Entity Brain's bunny spawn bool works as expected on easy mode" ) {
    test_random random_test;
    bool hardMode_test = false;
    Player testPlayer;
    Farmland testFarm(1, 1, &testPlayer, &random_test, &hardMode_test);
    Entity_Brain test_BunnyBrain(&testPlayer, &testFarm, &random_test, &hardMode_test);
    REQUIRE( test_BunnyBrain.hasBunnies() == false);
    REQUIRE( test_BunnyBrain.roll_make_bunny() == false);
    random_test.setN(65);
    REQUIRE( test_BunnyBrain.roll_make_bunny() == true);
    random_test.setN(64);
    REQUIRE( test_BunnyBrain.roll_make_bunny() == false);
    random_test.setN(0);
    REQUIRE( test_BunnyBrain.roll_make_bunny() == false);
}
TEST_CASE( "An Entity Brain's bunny spawn bool works as expected on HARD mode" ) {
    test_random random_test;
    bool hardMode_test = true;
    Player testPlayer;
    Farmland testFarm(4, 4, &testPlayer, &random_test, &hardMode_test);
    Entity_Brain test_BunnyBrain(&testPlayer, &testFarm, &random_test, &hardMode_test);
    REQUIRE( test_BunnyBrain.hasBunnies() == false);
    REQUIRE( test_BunnyBrain.roll_make_bunny() == false);
    random_test.setN(30);
    REQUIRE( test_BunnyBrain.roll_make_bunny() == true);
    random_test.setN(29);
    REQUIRE( test_BunnyBrain.roll_make_bunny() == false);
    random_test.setN(0);
    REQUIRE( test_BunnyBrain.roll_make_bunny() == false);
}

TEST_CASE( "The Entity Brain can make the Bunny appear on the farm" ) {
    bunny test_bun(3, 3, 0, 0);
    test_random random_test;
    bool hardMode_test = false;
    Player testPlayer;
    Farmland testFarm(5, 5, &testPlayer, &random_test, &hardMode_test);
    Entity_Brain test_BunnyBrain(&testPlayer, &testFarm, &random_test, &hardMode_test);
    REQUIRE( test_BunnyBrain.hasBunnies() == false);
    random_test.toggleNumFeed();
    random_test.setNumFeed({100, 1, 2});
    REQUIRE( testFarm.get_symbol(2, 4) == testPlayer.getAvatar());
    test_BunnyBrain.tick_brain();
    // a bunny has been made at (0, 2)
    REQUIRE( testFarm.get_symbol(0, 2) == test_bun.getAvatar());
    REQUIRE( test_BunnyBrain.hasBunnies() == true);
    random_test.setNumFeed({4, 10, 0});
    // the bunny will move RIGHT
    test_BunnyBrain.tick_brain();
    REQUIRE( testFarm.get_symbol(1, 2) == test_bun.getAvatar());

    // the bunny will move UP
    random_test.setNumFeed({1, 10, 0});
    test_BunnyBrain.tick_brain();
    REQUIRE( testFarm.get_symbol(1, 1) == test_bun.getAvatar());

    // the bunny will move LEFT
    random_test.setNumFeed({3, 10, 0});
    test_BunnyBrain.tick_brain();
    REQUIRE( testFarm.get_symbol(0, 1) == test_bun.getAvatar());

    // the bunny will move DOWN
    random_test.setNumFeed({2, 10, 0});
    test_BunnyBrain.tick_brain();
    REQUIRE( testFarm.get_symbol(0, 2) == test_bun.getAvatar());
}

TEST_CASE( "The Entity Brain will make the the bunny run 4 spaces away from the player" ) {
    bunny test_bun(3, 3, 0, 0);
    test_random random_test;
    bool hardMode_test = false;
    Player testPlayer;
    Farmland testFarm(7, 7, &testPlayer, &random_test, &hardMode_test);
    Entity_Brain test_BunnyBrain(&testPlayer, &testFarm, &random_test, &hardMode_test);
    REQUIRE( test_BunnyBrain.hasBunnies() == false);
    REQUIRE( testFarm.get_symbol(3, 6) == testPlayer.getAvatar());
    testPlayer.move_left();
    testPlayer.move_left();
    testPlayer.move_left();
    testPlayer.move_left();
    REQUIRE( testFarm.get_symbol(0, 6) == testPlayer.getAvatar());

    random_test.toggleNumFeed();
    random_test.setNumFeed({100, 1, 2});
    test_BunnyBrain.tick_brain();
    // a bunny has been made at (0, 2)
    REQUIRE( testFarm.get_symbol(0, 2) == test_bun.getAvatar());

    // set the bunny to be above the player
    random_test.setNumFeed({2, 10, 0});
    test_BunnyBrain.tick_brain();
    REQUIRE( testFarm.get_symbol(0, 3) == test_bun.getAvatar());
    random_test.setNumFeed({2, 10, 0});
    test_BunnyBrain.tick_brain();
    REQUIRE( testFarm.get_symbol(0, 4) == test_bun.getAvatar());
    random_test.setNumFeed({2, 10, 0});
    test_BunnyBrain.tick_brain();
    REQUIRE( testFarm.get_symbol(0, 5) == test_bun.getAvatar());

    random_test.toggleNumFeed();

    // on the next tick the bunny will "run" up 4 spaces
    test_BunnyBrain.tick_brain();
    REQUIRE( testFarm.get_symbol(0, 1) == test_bun.getAvatar());

    // move the bunny one to the right so its in position.
    random_test.setNumFeed({4, 10, 0});
    test_BunnyBrain.tick_brain();
    REQUIRE( testFarm.get_symbol(1, 1) == test_bun.getAvatar());

    // move the player up to (0,1) (to the left of the bunny)
    testPlayer.move_up();
    testPlayer.move_up();
    testPlayer.move_up();
    testPlayer.move_up();
    testPlayer.move_up();
    REQUIRE( testFarm.get_symbol(0, 1) == testPlayer.getAvatar());

    // the bunny will now run 4 spaces to the right.
    test_BunnyBrain.tick_brain();
    REQUIRE( testFarm.get_symbol(5, 1) == test_bun.getAvatar());

    // move the player up to (5, 0) (above the bunny)
    testPlayer.move_up();
    testPlayer.move_right();
    testPlayer.move_right();
    testPlayer.move_right();
    testPlayer.move_right();
    testPlayer.move_right();
    REQUIRE( testFarm.get_symbol(5, 0) == testPlayer.getAvatar());

    // the bunny will now run 4 spaces down.
    test_BunnyBrain.tick_brain();
    REQUIRE( testFarm.get_symbol(5, 5) == test_bun.getAvatar());

    // move the player to (6, 5) (to the right of the bunny)
    testPlayer.move_right();
    testPlayer.move_down();
    testPlayer.move_down();
    testPlayer.move_down();
    testPlayer.move_down();
    testPlayer.move_down();
    REQUIRE( testFarm.get_symbol(6, 5) == testPlayer.getAvatar());

    // the bunny will now run 4 spaces left.
    test_BunnyBrain.tick_brain();
    REQUIRE( testFarm.get_symbol(1, 5) == test_bun.getAvatar());

}

TEST_CASE( "The Entity Brain allows for bunnies to be chased out of bounds and go away." ) {
    bunny test_bun(3, 3, 0, 0);
    test_random random_test;
    bool hardMode_test = false;
    Player testPlayer;
    Farmland testFarm(7, 7, &testPlayer, &random_test, &hardMode_test);
    Entity_Brain test_BunnyBrain(&testPlayer, &testFarm, &random_test, &hardMode_test);
    REQUIRE( test_BunnyBrain.hasBunnies() == false);
    REQUIRE( testFarm.get_symbol(3, 6) == testPlayer.getAvatar());
    testPlayer.move_left();
    testPlayer.move_left();
    REQUIRE( testFarm.get_symbol(1, 6) == testPlayer.getAvatar());
    testPlayer.move_up();
    testPlayer.move_up();
    testPlayer.move_up();
    testPlayer.move_up();
    testPlayer.move_up();
    REQUIRE( testFarm.get_symbol(1, 1) == testPlayer.getAvatar());
    testPlayer.move_left();
    REQUIRE( testFarm.get_symbol(0, 1) == testPlayer.getAvatar());

    random_test.toggleNumFeed();
    random_test.setNumFeed({100, 1, 2});
    test_BunnyBrain.tick_brain();
    // a bunny has been made at (0, 2)
    REQUIRE( testFarm.get_symbol(0, 2) == test_bun.getAvatar());
    REQUIRE( test_BunnyBrain.hasBunnies() == true);

    random_test.toggleNumFeed();

    // on the next tick the bunny will flee down.
    test_BunnyBrain.tick_brain();
    REQUIRE( testFarm.get_symbol(0, 6) == test_bun.getAvatar());
    REQUIRE( test_BunnyBrain.hasBunnies() == true);
    testPlayer.move_down();
    testPlayer.move_down();
    testPlayer.move_down();
    testPlayer.move_down();
    REQUIRE( testFarm.get_symbol(0, 5) == testPlayer.getAvatar());

    // on the next tick the bunny will flee, and move 4 spaced down,
    //      move out of bounds, and then be deleted.
    test_BunnyBrain.tick_brain();
    REQUIRE( testFarm.get_symbol(0, 6) == "~"); // the symbol for Soil
    REQUIRE( test_BunnyBrain.hasBunnies() == false);
}