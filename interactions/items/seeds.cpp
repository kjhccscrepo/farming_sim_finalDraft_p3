#include "../item.hpp"
#include "seeds.hpp"
#include "../../plots/plant.hpp"
class item;

seeds::seeds(plant *plant_ptr) {
    myPlant = plant_ptr;
    myCost = 0;
    myName = (myPlant->myName() + " seeds");
    amount = 0;
}

std::string seeds::getMyName() {
    return myName;
}

void seeds::increase_quantity() {
    amount++;
}

void seeds::decrease_quantity() {
    amount--;
}

bool seeds::isSeed() {
    return true;
}

int seeds::quantity() {
    return amount;
}

plant *seeds::pointer() {
    return myPlant;
}

int seeds::getCost() {
    return myCost;
}

void seeds::setCost(int &cost) {
    myCost = cost;
}


seeds::~seeds() {
    myPlant = nullptr;
}

