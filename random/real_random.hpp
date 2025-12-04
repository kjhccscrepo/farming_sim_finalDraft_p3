#ifndef FARMING_SIM_REAL_RANDOM_HPP
#define FARMING_SIM_REAL_RANDOM_HPP
#include "frandom.hpp"
#include <random>
class real_random : public frandom {
public:
    explicit real_random();
    int get_random_number() override;
    int get_random_number_in_range(const int &minimum, const int &maximum) override;
};


#endif //FARMING_SIM_REAL_RANDOM_HPP