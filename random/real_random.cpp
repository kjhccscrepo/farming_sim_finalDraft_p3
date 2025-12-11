//
// Created by kistj on 12/3/2025.
//

#include "real_random.hpp"
#include <ctime>

real_random::real_random() {
    srand(time(nullptr));
}

int real_random::get_random_number() {
    return rand();
}

int real_random::get_random_number_in_range(const int &minimum, const int &maximum) {
    int inclusive_range = maximum - minimum + 1;

    return (rand() % inclusive_range) + minimum;
}
