
#include "farmland.hpp"
#include <iostream>
#include "../plots/soil.hpp"
#include "../plots/weeds/weed_classic.hpp"
#include "../entities/entity.hpp"
#include "../entities/bunny.hpp"
#include "../entities/player.hpp"
#include "../random/my_custom_random.hpp"


int Farmland::weedSpreadChance() const {
    if (*hard_mode == true) {
        return myRandom->get_random_number_in_range(0, 10);
    }
    return myRandom->get_random_number_in_range(-2, 5);
}

int Farmland::isCrowded(const int &x, const int &y) const {
    if (myPlayer->getX() == x && myPlayer->getY() == y) {
        return 1;
    }
    if (!myBunniesPtr.empty()) {
        if (x > 0 && x < rows && y > 0 && y < columns) {
            if (get_symbol(x, y) == "+") {
                return 2;
            }
        }
    }
    return 0;
}

Farmland::Farmland(const int ini_rows, const int ini_columns, Player *player_ptr, my_custom_random *random_ptr, bool *hmBool) {
    myPlayer = player_ptr;
    myRandom = random_ptr;
    hard_mode = hmBool;
    rows = ini_rows;
    columns = ini_columns;
    myPlayer->set_bounds(ini_rows, ini_columns);
    myPlayer->better_start_position();
    for (int i = 0; i < ini_rows; i++) {
        std::vector<Plot*> row;
        for (int j = 0; j < ini_columns; j++) {
            const auto new_plot = new Soil();
            row.push_back(new_plot);
        }
        plots.push_back(row);
    }
    dayCounter = 1;
}

void Farmland::toggle_weed_spead() {
    if (!makeWeeds) makeWeeds = true;
    else makeWeeds = false;
}

int Farmland::harvest_val() const {
    if (plots[myPlayer->getX()][myPlayer->getY()] != nullptr) {
        return plots[myPlayer->getX()][myPlayer->getY()]->harvest();
    }
    return 0;
}

int Farmland::harvest_val(const int x, const int y) const {
    if (plots[x][y] != nullptr) {
        return plots[x][y]->harvest();
    }
    return 0;
}

int Farmland::row_capacity() const {
    return rows;
}

int Farmland::column_capacity() const {
    return columns;
}

std::string Farmland::get_symbol(const int x, const int y) const {
    if (myPlayer->getX() == x && myPlayer->getY() == y) {
        return myPlayer->getAvatar();
    }
    if (!myBunniesPtr.empty()) {
        for (const auto &i : myBunniesPtr) {
            if (i->getX() == x && i->getY() == y) {
                return i->getAvatar();
            }
        }
    }
    return plots[x][y]->symbol();
}

int Farmland::getDays() const {
    return dayCounter;
}

void Farmland::plant(const int row, const int column, Plot *new_plot) {
    const Plot *current_plot = plots.at(row).at(column);
    plots.at(row).at(column) = new_plot;
    delete current_plot;
}

void Farmland::end_day() {
    xBuffer.clear();
    xBuffer = {};
    yBuffer.clear();
    yBuffer = {};
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (plots.at(i).at(j)->harvest() == -10) { // it's a weed and should spread
                xBuffer.push_back(i);
                yBuffer.push_back(j);
            } else {
                plots.at(i).at(j)->end_day();
            }
        }
    }
    if (xBuffer.size() == yBuffer.size() && !xBuffer.empty() && !yBuffer.empty() && makeWeeds) {
        for (int i = 0; i < xBuffer.size(); i++) {
            const int direction = myRandom->get_random_number_in_range(0, 1);
            if (direction == 0) {
                const int up_down = myRandom->get_random_number_in_range(0, 1);
                if (up_down == 0) {
                    if (yBuffer[i] + 1 < column_capacity()) {
                        if (const int r = weedSpreadChance(); r > 4) {
                            const auto weed = new weed_classic();
                            plant(xBuffer[i], yBuffer[i] + 1, weed);
                        }
                    }
                } else {
                    if (yBuffer[i] - 1 > 0) {
                        if (const int r = weedSpreadChance(); r > 4) {
                            const auto weed = new weed_classic();
                            plant(xBuffer[i], yBuffer[i] - 1, weed);
                        }
                    }
                }
            } else {
                const int left_right = myRandom->get_random_number_in_range(0, 1);
                if (left_right == 0) {
                    if (xBuffer[i] - 1 > 0) {
                        if (const int r = weedSpreadChance(); r > 4) {
                            const auto weed = new weed_classic();
                            plant(xBuffer[i] - 1, yBuffer[i], weed);
                        }
                    }
                } else {
                    if (xBuffer[i] + 1 < row_capacity()) {
                        if (const int r = weedSpreadChance(); r > 4) {
                            const auto weed = new weed_classic();
                            plant(xBuffer[i] + 1, yBuffer[i], weed);
                        }
                    }
                }
            }
        }
    }
    dayCounter = 1 + dayCounter;
}

void Farmland::set_soil() {
    plots[myPlayer->getX()][myPlayer->getY()] = new Soil();
    plots[myPlayer->getX()][myPlayer->getY()]->end_day();
}

void Farmland::water_plot() const {
    if (plots[myPlayer->getX()][myPlayer->getY()]->harvest() == -3) {
        plots[myPlayer->getX()][myPlayer->getY()]->water();
    }
}

Plot *Farmland::current_plot() const {
    return plots[myPlayer->getX()][myPlayer->getY()];
}

void Farmland::move_player_up() const {
    if (isCrowded(myPlayer->getX(), myPlayer->getY() - 1) == 0) {
        myPlayer->move_up();
    }
}
void Farmland::move_player_down() const {
    if (isCrowded(myPlayer->getX(), myPlayer->getY() + 1) == 0) {
        myPlayer->move_down();
    }
}
void Farmland::move_player_right() const {
    if (isCrowded(myPlayer->getX() + 1, myPlayer->getY()) == 0) {
        myPlayer->move_right();
    }
}
void Farmland::move_player_left() const {
    if (isCrowded(myPlayer->getX() - 1, myPlayer->getY()) == 0) {
        myPlayer->move_left();
    }
}

char Farmland::bunny_player_check(const bunny *b_ptr) const {
    if (b_ptr == nullptr) {
        return '0';
    }
    if (b_ptr->getX() == myPlayer->getX()) {
        if (b_ptr->getY() == myPlayer->getY() + 1) {
            return 'A';
        }
        if (b_ptr->getY() == myPlayer->getY() - 1) {
            return 'B';
        }
    } else if (b_ptr->getY() == myPlayer->getY()) {
        if (b_ptr->getX() == myPlayer->getX() + 1) {
            return 'L';
        }
        if (b_ptr->getX() == myPlayer->getX() - 1) {
            return 'R';
        }
    }
    return 'G';
}

void Farmland::bunny_eat(const bunny *b_ptr) {
    if (b_ptr->is_out_of_bounds() == false) {
        plots[b_ptr->getX()][b_ptr->getY()] = new Soil();
        plots[b_ptr->getX()][b_ptr->getY()]->end_day();
    }
}


void Farmland::find_valid_bunny_spawn(int &x, int &y) {
    const int REGION = myRandom->get_random_number_in_range(1, 4);
    if (REGION == 1) {
        x = 0;
        y = myRandom->get_random_number_in_range(0, columns - 1);
    }
    else if (REGION == 2) {
        x = rows - 1;
        y = myRandom->get_random_number_in_range(0, columns - 1);
    }
    else if (REGION == 3) {
        x = myRandom->get_random_number_in_range(0, rows - 1);
        y = columns - 1;
    }
    else {
        x = myRandom->get_random_number_in_range(0, rows - 1);
        y = 0;
    }
    if (isCrowded(x, y) != 0) {
        find_valid_bunny_spawn(x, y);
    }
}
