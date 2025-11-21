//
// Created by kistj on 11/18/2025.
//

#ifndef FARMING_SIMULATOR_V2C_FARM_HPP
#define FARMING_SIMULATOR_V2C_FARM_HPP

#include <string>
#include <vector>
#include "player.hpp"
#include "../plots/plot.hpp"
#include "../plots/soil.hpp"
#include "../plots/weeds/weed_classic.hpp"

class Farm {
private:
    bool makeWeeds{true};
    int rows;
    int columns;
    Player *myPlayer;
    int dayCounter;
    std::vector<std::vector<Plot*>> plots;
    std::vector<int> xBuffer;
    std::vector<int> yBuffer;
public:
    explicit Farm(int ini_rows, int ini_columns);

    void toggle_weeds();

    void link_Player(Player *player_ptr);

    [[nodiscard]] int harvest_val() const;

    [[nodiscard]] int harvest_val(int x, int y) const;

    [[nodiscard]] int row_capacity() const;

    [[nodiscard]] int column_capacity() const;

    [[nodiscard]] std::string get_symbol(int x, int y) const;

    [[nodiscard]] int getDays() const;

    void plant(int row, int column, Plot *new_plot);

    void end_day();

    void set_soil();

    void water_plot() const;

    [[nodiscard]] Plot *current_plot() const;
};
#endif //FARMING_SIMULATOR_V2C_FARM_HPP