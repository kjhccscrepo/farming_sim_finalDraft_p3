//
// Created by kistj on 11/18/2025.
//

#ifndef FARMING_SIMULATOR_V2C_BRUSSEL_SPROUTS_HPP
#define FARMING_SIMULATOR_V2C_BRUSSEL_SPROUTS_HPP

#include <vector>
#include "../plant.hpp"

class Brussels_Sprouts final : public plant {
public:
    Brussels_Sprouts() {
        setName("Brussels Sprouts");
        setAge(1);
        setMatureTime(16);
        setWeightedStates({5, 10});
        setStates({"x", "e", "E"});
        setSeedDrops({8, 9, 10, 12, 13});
        setWeightedOddsSeeds({90, 30, 10, 5, 1});
        setProduceDrops({4, 6, 7, 8, 9});
        setWeightedOddsProduces({10, 15, 20, 15, 10});
        setCost(3);
    }
};
#endif //FARMING_SIMULATOR_V2C_BRUSSEL_SPROUTS_HPP