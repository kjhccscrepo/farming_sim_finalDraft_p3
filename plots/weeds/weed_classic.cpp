//
// Created by kistj on 11/18/2025.
//

#include "weed_classic.hpp"
#include "../plot.hpp"

weed_classic::weed_classic() = default;

std::string weed_classic::symbol() {
    return sym;
}

std::string weed_classic::myName() {
    return name;
}

void weed_classic::end_day() {
    // check down
}

int weed_classic::harvest() {
    return -10;
}

void weed_classic::water() {
    // no - op
}

weed_classic::~weed_classic() = default;

item * weed_classic::seedPointer() {
    return nullptr;
}

item * weed_classic::producePointer() {
    return nullptr;
}

int weed_classic::seedDrops() {
    return 0;
}

int weed_classic::produceDrops() {
    return 0;
}
