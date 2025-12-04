//
// Created by kistj on 12/3/2025.
//

#ifndef FARMING_SIM_TEST_RANDOM_HPP
#define FARMING_SIM_TEST_RANDOM_HPP
#include "frandom.hpp"

class test_random : public frandom {
public:
    int myNum;
    int get_random_number() override;
    int get_random_number_in_range(const int &minimum, const int &maximum) override;
};


#endif //FARMING_SIM_TEST_RANDOM_HPP