#ifndef FARMING_SIM_REAL_RANDOM_HPP
#define FARMING_SIM_REAL_RANDOM_HPP
#include "my_custom_random.hpp"
#include <random>
class real_random final : public my_custom_random {
public:
    explicit real_random();
    int get_random_number() override;
    int get_random_number_in_range(const int &minimum, const int &maximum) override;
};


#endif //FARMING_SIM_REAL_RANDOM_HPP