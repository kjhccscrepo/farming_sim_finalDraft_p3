#include "../../entities/player.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>


TEST_CASE( "it starts the player in 0, 0 by default" ) {
    const Player test_player;
    REQUIRE( test_player.getX() == 0 );
    REQUIRE( test_player.getY() == 0 );
}
TEST_CASE( "it starts the player in a smart, calculated bottom middle position" ) {
    Player test_player;
    test_player.set_bounds(3, 3);
    test_player.better_start_position();
    REQUIRE( test_player.getX() == 1 );
    REQUIRE( test_player.getY() == 2 );
}
TEST_CASE( "it moves the player to the right" ) {
    Player test_player;
    test_player.set_bounds(3, 3);
    test_player.move_right();
    REQUIRE( test_player.getX() == 1 );
    REQUIRE( test_player.getY() == 0 );
}
TEST_CASE( "it moves the player down" ) {
    Player test_player;
    test_player.set_bounds(3, 3);
    test_player.move_down();
    REQUIRE( test_player.getX() == 0 );
    REQUIRE( test_player.getY() == 1 );
}
TEST_CASE( "it moves the player up" ) {
    Player test_player;
    test_player.set_bounds(3, 3);
    test_player.better_start_position();
    REQUIRE( test_player.getX() == 1 );
    REQUIRE( test_player.getY() == 2 );
    test_player.move_up();
    REQUIRE( test_player.getX() == 1 );
    REQUIRE( test_player.getY() == 1 );
}
TEST_CASE( "it moves the player left" ) {
    Player test_player;
    test_player.set_bounds(3, 3);
    test_player.better_start_position();
    REQUIRE( test_player.getX() == 1 );
    REQUIRE( test_player.getY() == 2 );
    test_player.move_left();
    REQUIRE( test_player.getX() == 0 );
    REQUIRE( test_player.getY() == 2 );
}
TEST_CASE( "the avatar works" ) {
    Player test_player;
    REQUIRE( test_player.getAvatar() == "@" );
    test_player.change_avatar("A");
    REQUIRE( test_player.getAvatar() == "A" );
    test_player.change_avatar("P");
    REQUIRE( test_player.getAvatar() == "P" );
}