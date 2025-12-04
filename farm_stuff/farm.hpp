//
// Created by kistj on 11/18/2025.
//

#ifndef FARMING_SIMULATOR_V2C_FARM_HPP
#define FARMING_SIMULATOR_V2C_FARM_HPP

#include <string>
#include <vector>
#include "../entities/player.hpp"
#include "../plots/plot.hpp"
#include "../plots/soil.hpp"
#include "../plots/weeds/weed_classic.hpp"
#include "../entities/bunny.hpp"
#include "../random/frandom.hpp"

class Farm {
private:
    frandom *myRandom;

    bool makeWeeds{true};
    int rows;
    int columns;
    Player *myPlayer;
    int dayCounter;
    std::vector<std::vector<Plot*>> plots;
    std::vector<int> xBuffer;
    std::vector<int> yBuffer;

    std::vector<bunny*> bunnies;
    bool hardmode;

    int max_bunnies() const;

    bool roll_make_bunnies() const;

    int weedSpreadChance() const;

    bool isCrowded(const int &x, const int &y) const;

public:
    explicit Farm(int ini_rows, int ini_columns);

    void set_hardmode();

    void set_Random(frandom *frandom_ptr);

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

    // new collision code
    void move_player_up() const;
    void move_player_down() const;
    void move_player_right() const;
    void move_player_left() const;


    // bunny code
    void bunnie_spawn();


};
#endif //FARMING_SIMULATOR_V2C_FARM_HPP