//
// Created by kistj on 11/18/2025.
//

#ifndef FARMING_SIMULATOR_V2C_FARMLAND_HPP
#define FARMING_SIMULATOR_V2C_FARMLAND_HPP

#include <string>
#include <vector>
#include "../entities/entity.hpp"
#include "../entities/player.hpp"
#include "../plots/plot.hpp"
#include "../plots/soil.hpp"
#include "../plots/weeds/weed_classic.hpp"
#include "../entities/bunny.hpp"
#include "../random/my_custom_random.hpp"

class Farmland {
private:
    my_custom_random *myRandom;
    bool *hard_mode;
    bool makeWeeds{true};
    int rows;
    int columns;
    Player *myPlayer;
    int dayCounter;
    std::vector<std::vector<Plot*>> plots;
    std::vector<int> xBuffer;
    std::vector<int> yBuffer;
    [[nodiscard]] int weedSpreadChance() const;
    [[nodiscard]] int isCrowded(const int &x, const int &y) const;

public:
    std::vector<bunny*> myBunniesPtr;

    explicit Farmland(int ini_rows, int ini_columns, Player *player_ptr, my_custom_random *random_ptr, bool *hmBool);

    void toggle_weed_spead();

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
    char bunny_player_check(const bunny *b_ptr) const;

    void bunny_eat(const bunny *b_ptr);

    void find_valid_bunny_spawn(int &x, int &y);

};
#endif