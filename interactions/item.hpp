//
// Created by kistj on 11/18/2025.
//

#ifndef FARMING_SIMULATOR_V2C_ITEM_HPP
#define FARMING_SIMULATOR_V2C_ITEM_HPP

#include "../plots/plant.hpp"
#include <string>

class plant;

// abstract base class
class item {
public:
    virtual ~item() = default;

    virtual std::string getMyName() = 0;

    virtual bool isSeed() = 0;

    virtual void increase_quantity() = 0;

    virtual void decrease_quantity() = 0;

    virtual int quantity() = 0;

    virtual plant *pointer() = 0;

    virtual int getCost() = 0;

    virtual void setCost(int &cost) = 0;
};
#endif //FARMING_SIMULATOR_V2C_ITEM_HPP
