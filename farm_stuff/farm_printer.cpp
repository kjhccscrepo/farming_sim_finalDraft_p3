//
// Created by kistj on 11/18/2025.
//


#include "farm_printer.hpp"

FarmPrinter::FarmPrinter(Farmland *farm_ptr) : farm_to_print(farm_ptr) {
}

std::stringstream FarmPrinter::prettyPrint() const {
    std::stringstream output;
    // get top border
    for (int x = 0; x < farm_to_print->row_capacity() + 2; x++) {
        output << "/";
        output << " ";
    }
    output << "\n";
    for (int y = 0; y < farm_to_print->column_capacity(); y++) {
        for (int x2 = 0; x2 < farm_to_print->row_capacity() + 2; x2++) {
            if (x2 == 0 || x2 == farm_to_print->row_capacity() + 1) {
                output << "/";
                output << " ";
            } else {
                output << farm_to_print->get_symbol(x2 - 1, y);
                output << " ";
            }
        }
        output << "\n";
    }
    // get the bottom border
    for (int x = 0; x < farm_to_print->row_capacity() + 2; x++) {
        output << "/";
        output << " ";
    }
    output << "\n";
    return output;
}

int FarmPrinter::days_to_print() const {
    return farm_to_print->getDays();
}
