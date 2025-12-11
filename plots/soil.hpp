#ifndef SOIL_HPP
#define SOIL_HPP

#include <string>
#include "plot.hpp"
class Plot;

class Soil final : public Plot {
public:
    ~Soil() override;

    std::string symbol() override;

    std::string myName() override;

    void end_day() override;

    int harvest() override;

    void water() override;

    item *seedPointer() override;

    item *producePointer() override;

    int seedDrops() override;

    int produceDrops() override;
};
#endif