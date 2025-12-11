//
// Created by kistj on 11/18/2025.
//
#include "soil.hpp"
Soil::~Soil() = default;

std::string Soil::symbol() {
    return "~";
}

std::string Soil::myName() {
    return "soil";
}

void Soil::end_day() {
    // no-op
}
int Soil::harvest() {
    return -1;
}

void Soil::water() {
    // no-op
}

item *Soil::seedPointer() {
    return nullptr;
}

item *Soil::producePointer() {
    return nullptr;
}

int Soil::seedDrops() {
    return 0;
}

int Soil::produceDrops() {
    return 0;
}