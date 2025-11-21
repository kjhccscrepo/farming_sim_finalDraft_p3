//
// Created by kistj on 11/18/2025.
//

#include "produce.hpp"
#include "../../plots/plant.hpp"

produce::produce(plant *plant_ptr) {
    myPlant = plant_ptr;
    mySell = 0;
    myName = (myPlant->myName() + "(s)");
    amount = 0;
}

std::string produce::getMyName() {
    return myName;
}

void produce::increase_quantity() {
    amount++;
}

void produce::decrease_quantity() {
    amount--;
}

bool produce::isSeed() {
    return false;
}

int produce::quantity() {
    return amount;
}

plant *produce::pointer() {
    return myPlant;
}

int produce::getCost() {
    if ((mySell / 3) <= 0) {
        return 1;
    }
    return (mySell / 3);
}

void produce::setCost(int &cost) {
    mySell = cost;
}

produce::~produce() {
    myPlant = nullptr;
}
