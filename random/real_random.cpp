//
// Created by kistj on 12/3/2025.
//

#include "real_random.hpp"

real_random::real_random() {
    srand(time_t(nullptr));
}

int real_random::get_random_number() {
    return rand();
}

int real_random::get_random_number_in_range(const int &minimum, const int &maximum) {
    return minimum + rand() % (maximum - minimum);
}
