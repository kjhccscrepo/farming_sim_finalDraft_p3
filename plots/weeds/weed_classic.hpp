//
// Created by kistj on 11/18/2025.
//

#ifndef WEED_CLASSIC_HPP
#define WEED_CLASSIC_HPP
#include <random>
#include <string>
#include "../plot.hpp"

class weed_classic final : public Plot {
private:
    std::string name = "Common Weed";
    std::string sym = "*";

public:
    explicit weed_classic();

    std::string symbol() override;

    std::string myName() override;

    void end_day() override;

    int harvest() override;

    void water() override;

    ~weed_classic() override;

    item *seedPointer() override;

    item *producePointer() override;

    int seedDrops() override;

    int produceDrops() override;
};

#endif