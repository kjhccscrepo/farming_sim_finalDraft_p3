//
// Created by kistj on 12/6/2025.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include "../random/real_random.hpp"
#include "../random/test_random.hpp"
real_random test_real_random;
test_random test_random;
constexpr int roll_times = 25;
TEST_CASE( "Can gen 1 thru 4 randomly" ) {
    std::vector<int> results;
    for (int i = 0; i < roll_times; ++i) {
        results.push_back(test_real_random.get_random_number_in_range(1, 4));
        REQUIRE(1 <= results[i]);
        REQUIRE(results[i] <= 4);
    }
}

TEST_CASE( "Can gen 9 thru 72 randomly" ) {
    std::vector<int> results;
    for (int i = 0; i < roll_times; ++i) {
        results.push_back(test_real_random.get_random_number_in_range(9, 72));
        REQUIRE(9 <= results[i]);
        REQUIRE(results[i] <= 72);
    }
}

TEST_CASE( "Test Random can be used to manipulate a value one at a time") {
    std::vector<int> results;
    test_random.setN(2);
    results.push_back(test_random.get_random_number_in_range(1, 4));
    results.push_back(test_random.get_random_number());
    test_random.setN(1);
    results.push_back(test_random.get_random_number_in_range(9000000, 2));
    results.push_back(test_random.get_random_number());
    test_random.setN(0);
    results.push_back(test_random.get_random_number_in_range(111111111, 1111111111));
    results.push_back(test_random.get_random_number());
    REQUIRE(results[0] == 2);
    REQUIRE(results[1] == 2);
    REQUIRE(results[2] == 1);
    REQUIRE(results[3] == 1);
    REQUIRE(results[4] == 0);
    REQUIRE(results[5] == 0);
}
TEST_CASE( "Test Random can have a number feed that its iterates thru for better testing") {
    test_random.setNumFeed({1, 1, 2, 2, 5, 6, 0, 9});
    std::vector<int> results;
    results.push_back(test_random.get_random_number_in_range(1, 4));
    results.push_back(test_random.get_random_number());
    results.push_back(test_random.get_random_number_in_range(9000000, 2));
    results.push_back(test_random.get_random_number());
    results.push_back(test_random.get_random_number_in_range(111111111, 1111111111));
    results.push_back(test_random.get_random_number());
    results.push_back(test_random.get_random_number());
    results.push_back(test_random.get_random_number());
    REQUIRE(results[0] == 1);
    REQUIRE(results[1] == 1);
    REQUIRE(results[2] == 2);
    REQUIRE(results[3] == 2);
    REQUIRE(results[4] == 5);
    REQUIRE(results[5] == 6);
    REQUIRE(results[6] == 0);
    REQUIRE(results[7] == 9);
}
TEST_CASE( "Test Random's number feed can be have values pushed") {
    test_random.setNumFeed({0, 0, 1, 0});
    std::vector<int> results;
    results.push_back(test_random.get_random_number_in_range(1, 4));
    results.push_back(test_random.get_random_number());
    results.push_back(test_random.get_random_number_in_range(9000000, 2));
    results.push_back(test_random.get_random_number());
    results.push_back(test_random.get_random_number_in_range(111111111, 1111111111));
    results.push_back(test_random.get_random_number());
    results.push_back(test_random.get_random_number());
    results.push_back(test_random.get_random_number());
    REQUIRE(results[0] == 0);
    REQUIRE(results[1] == 0);
    REQUIRE(results[2] == 1);
    REQUIRE(results[3] == 0);
    REQUIRE(results[4] == 0);
    REQUIRE(results[5] == 0);
    REQUIRE(results[6] == 1);
    REQUIRE(results[7] == 0);
    test_random.pushNumFeed(3);
    results.push_back(test_random.get_random_number());
    results.push_back(test_random.get_random_number());
    results.push_back(test_random.get_random_number());
    results.push_back(test_random.get_random_number());
    results.push_back(test_random.get_random_number());
    results.push_back(test_random.get_random_number());
    REQUIRE(results[8] == 3 );
    REQUIRE(results[9] == 0 );
    REQUIRE(results[10] == 0);
    REQUIRE(results[11] == 1);
    REQUIRE(results[12] == 0);
    REQUIRE(results[13] == 3);
}

