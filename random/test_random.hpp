//
// Created by kistj on 12/3/2025.
//

#ifndef FARMING_SIM_TEST_RANDOM_HPP
#define FARMING_SIM_TEST_RANDOM_HPP
#include <vector>
#include "my_custom_random.hpp"

class test_random final : public my_custom_random {
    int myNum = 0;
    bool use_feed = false;
    std::vector<int> number_Feed_tape;
    int numFeedIterator = 0;
    int getNumFromFeed();
    int getMyNum();
public:
    void setN(const int &n);
    void toggleNumFeed();
    void pushNumFeed(const int &n);
    void clearNumFeed();
    void setNumFeed(const std::vector<int> &newNumFeed);
    int get_random_number() override;
    int get_random_number_in_range(const int &minimum, const int &maximum) override;
};
#endif