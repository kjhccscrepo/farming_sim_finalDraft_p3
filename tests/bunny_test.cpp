//
// Created by kistj on 12/11/2025.
//
#include "../entities/bunny.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>


TEST_CASE( "A Bunny can be initialized at (0, 0)" ) {
    bunny testBun(3, 3, 0, 0);
    REQUIRE( testBun.getX() == 0 );
    REQUIRE( testBun.getY() == 0 );
}

TEST_CASE( "A Bunny can move right" ) {
    bunny testBun(3, 3, 0, 0);
    testBun.move_right();
    REQUIRE( testBun.getX() == 1 );
    REQUIRE( testBun.getY() == 0 );
}
TEST_CASE( "A Bunny can move down" ) {
    bunny testBun(3, 3, 0, 0);
    testBun.move_down();
    REQUIRE( testBun.getX() == 0 );
    REQUIRE( testBun.getY() == 1 );
}
TEST_CASE( "A Bunny can move left" ) {
    bunny testBun(3, 3, 3, 3);
    testBun.move_left();
    REQUIRE( testBun.getX() == 2 );
    REQUIRE( testBun.getY() == 3 );
}
TEST_CASE( "A Bunny can move up" ) {
    bunny testBun(3, 3, 3, 3);
    testBun.move_up();
    REQUIRE( testBun.getX() == 3 );
    REQUIRE( testBun.getY() == 2 );
}
TEST_CASE( "A Bunny's avatar works" ) {
    bunny testBun(3, 3, 3, 3);
    REQUIRE( testBun.getAvatar() == "+" );
}
TEST_CASE( "A Bunny's age is tracked" ) {
    bunny testBun(3, 3, 3, 3);
    REQUIRE( testBun.getAge() == 0 );
    testBun.tick();
    REQUIRE( testBun.getAge() == 1 );
    testBun.tick();
    testBun.tick();
    testBun.tick();
    REQUIRE( testBun.getAge() == 4 );
}

TEST_CASE( "Bunnies unique out of Bounds handling works" ) {
    bunny bound_Bunny_test(2, 2, 0, 0);
    REQUIRE( bound_Bunny_test.getX() == 0 );
    REQUIRE( bound_Bunny_test.getY() == 0 );
    REQUIRE( bound_Bunny_test.is_out_of_bounds() == false);
    bound_Bunny_test.move_up();
    REQUIRE( bound_Bunny_test.getY() == -1 );
    REQUIRE( bound_Bunny_test.is_out_of_bounds() == true);
    bound_Bunny_test.move_down();
    REQUIRE( bound_Bunny_test.getY() == 0 );
    REQUIRE( bound_Bunny_test.is_out_of_bounds() == false);
    bound_Bunny_test.move_left();
    REQUIRE( bound_Bunny_test.getX() == -1 );
    REQUIRE( bound_Bunny_test.is_out_of_bounds() == true);
    bound_Bunny_test.move_right();
    REQUIRE( bound_Bunny_test.getX() == 0 );
    REQUIRE( bound_Bunny_test.is_out_of_bounds() == false);
    bound_Bunny_test.move_right();
    REQUIRE( bound_Bunny_test.getX() == 1 );
    REQUIRE( bound_Bunny_test.is_out_of_bounds() == false);
    bound_Bunny_test.move_right();
    REQUIRE( bound_Bunny_test.getX() == 2 );
    REQUIRE( bound_Bunny_test.is_out_of_bounds() == true);
}