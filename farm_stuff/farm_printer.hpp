//
// Created by kistj on 11/18/2025.
//

#ifndef FARMING_SIMULATOR_V2C_FARM_PRINTER_HPP
#define FARMING_SIMULATOR_V2C_FARM_PRINTER_HPP
#include <sstream>
#include "farmland.hpp"


class FarmPrinter {
private:
    Farmland *farm_to_print;

public:
    explicit FarmPrinter(Farmland *farm_ptr);

    [[nodiscard]] std::stringstream prettyPrint() const;

    [[nodiscard]] int days_to_print() const;
};

#endif //FARMING_SIMULATOR_V2C_FARM_PRINTER_HPP