//
// Created by kistj on 11/18/2025.
//

#ifndef PORFOLIO_2_CS122_BEET_HPP
#define PORFOLIO_2_CS122_BEET_HPP
#include <vector>
#include "../plant.hpp"
class Beet final : public plant {
public:
    Beet() {
        setName("Beet");
        setAge(1);
        setMatureTime(8);
        setWeightedStates({2, 5});
        setStates({"x", "b", "B"});
        setCost(4);
        setSeedDrops({1, 2});
        setWeightedOddsSeeds({30, 20});
        setProduceDrops({1, 2});
        setWeightedOddsProduces({40, 30});
    }
};



#endif