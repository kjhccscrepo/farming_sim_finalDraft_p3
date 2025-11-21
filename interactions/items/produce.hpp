#ifndef FARMING_SIMULATOR_V2C_PRODUCE_HPP
#define FARMING_SIMULATOR_V2C_PRODUCE_HPP

#include "../item.hpp"
class produce final : public item {
private:
    plant *myPlant;
    std::string myName;
    int amount;
    int mySell;

public:
    ~produce() override;

    explicit produce(plant *plant_ptr);

    std::string getMyName() override;

    void increase_quantity() override;

    void decrease_quantity() override;

    bool isSeed() override;

    int quantity() override;

    plant *pointer() override;

    int getCost() override;

    void setCost(int &cost) override;

};

#endif