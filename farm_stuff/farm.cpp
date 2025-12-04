
#include "farm.hpp"
#include "../plots/soil.hpp"
#include "../plots/weeds/weed_classic.hpp"
#include <random>
#include "../entities/entity.hpp"
#include "../entities/bunny.hpp"
#include "../random/frandom.hpp"

int Farm::max_bunnies() const {
    if (hardmode) return 10;
    return 4;
}

bool Farm::roll_make_bunnies() const {
    if (bunnies.size() < this->max_bunnies()) {
        if (myRandom->get_random_number_in_range(0, 11) > 5) return true;
    }
    return false;
}

int Farm::weedSpreadChance() const {
    if (hardmode) return 1;
    return myRandom->get_random_number_in_range(1, 9);
}

bool Farm::isCrowded(const int &x, const int &y) const {
    if (myPlayer->getX() == x && myPlayer->getY() == y) {
        return true;
    }
    if (!bunnies.empty()) {
        for (int i = 0; i < bunnies.size(); i++) {
            if (bunnies[i]->getX() == x && bunnies[i]->getY() == y) {
                return true;
            }
        }
    }
    return false;
}

Farm::Farm(const int ini_rows, const int ini_columns) {
    hardmode = false;
    myRandom = nullptr;
    myPlayer = nullptr;
    rows = ini_rows;
    columns = ini_columns;
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

void Farm::set_hardmode() {
    hardmode = true;
}

void Farm::set_Random(frandom *frandom_ptr) {
    myRandom = frandom_ptr;
}

void Farm::toggle_weeds() {
    if (!makeWeeds) makeWeeds = true;
    else makeWeeds = false;
}

void Farm::link_Player(Player *player_ptr) {
    myPlayer = player_ptr;
}

int Farm::harvest_val() const {
    if (plots[myPlayer->getX()][myPlayer->getY()] != nullptr) {
        return plots[myPlayer->getX()][myPlayer->getY()]->harvest();
    }
    return 0;
}

int Farm::harvest_val(const int x, const int y) const {
    if (plots[x][y] != nullptr) {
        return plots[x][y]->harvest();
    }
    return 0;
}

int Farm::row_capacity() const {
    return rows;
}

int Farm::column_capacity() const {
    return columns;
}

std::string Farm::get_symbol(const int x, const int y) const {
    if (myPlayer->getX() == x && myPlayer->getY() == y) {
        return myPlayer->getAvatar();
    } else {
        return plots[x][y]->symbol();
    }
}

int Farm::getDays() const {
    return dayCounter;
}

void Farm::plant(const int row, const int column, Plot *new_plot) {
    const Plot *current_plot = plots.at(row).at(column);
    plots.at(row).at(column) = new_plot;
    delete current_plot;
}

void Farm::end_day() {
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
        const int xMax = row_capacity();
        const int yMax = column_capacity();

        for (int i = 0; i < xBuffer.size(); i++) {
            if (xBuffer[i] > 0) {
                if (const int r = weedSpreadChance(); r > 4) {
                    const auto weed = new weed_classic();
                    plant(xBuffer[i] - 1, yBuffer[i], weed);
                }
            }
            if (yBuffer[i] > 0) {
                if (const int r = weedSpreadChance(); r > 4) {
                    const auto weed = new weed_classic();
                    plant(xBuffer[i], yBuffer[i] - 1, weed);
                }
            }
            if (xBuffer[i] < xMax - 1) {
                if (const int r = weedSpreadChance(); r > 4) {
                    const auto weed = new weed_classic();
                    plant(xBuffer[i] + 1, yBuffer[i], weed);
                }
            }
            if (yBuffer[i] < yMax - 1) {
                if (const int r = weedSpreadChance(); r > 4) {
                    const auto weed = new weed_classic();
                    plots[xBuffer[i]][yBuffer[i] + 1] = weed;
                }
            }
        }
    }
    dayCounter = 1 + dayCounter;
}

void Farm::set_soil() {
    plots[myPlayer->getX()][myPlayer->getY()] = new Soil();
    plots[myPlayer->getX()][myPlayer->getY()]->end_day();
}

void Farm::water_plot() const {
    if (plots[myPlayer->getX()][myPlayer->getY()]->harvest() == -3) {
        plots[myPlayer->getX()][myPlayer->getY()]->water();
    }
}

Plot *Farm::current_plot() const {
    return plots[myPlayer->getX()][myPlayer->getY()];
}

void Farm::move_player_up() const {
    if (isCrowded(myPlayer->getX(), myPlayer->getY() - 1)) {
        myPlayer->move_up();
    }
}
void Farm::move_player_down() const {
    if (isCrowded(myPlayer->getX(), myPlayer->getY() + 1)) {
        myPlayer->move_up();
    }
}
void Farm::move_player_right() const {
    if (isCrowded(myPlayer->getX() + 1, myPlayer->getY())) {
        myPlayer->move_up();
    }
}
void Farm::move_player_left() const {
    if (isCrowded(myPlayer->getX() - 1, myPlayer->getY())) {
        myPlayer->move_up();
    }
}

void Farm::bunnie_spawn() {
    if (roll_make_bunnies()) {
        int bunnyCords[2];
        while (true) { // until a valid spawn location is found
            const int REGION = myRandom->get_random_number_in_range(1, 4);
            if (REGION == 1) {
                bunnyCords[0] = 0;
                bunnyCords[1] = myRandom->get_random_number_in_range(0, columns - 1);
            }
            else if (REGION == 2) {
                bunnyCords[0] = myRandom->get_random_number_in_range(rows - 1, 0);
                bunnyCords[1] = 0;
            }
            else if (REGION == 3) {
                bunnyCords[0] = columns - 1;
                bunnyCords[1] = myRandom->get_random_number_in_range(0, columns - 1);
            }
            else if (REGION == 4) {
                bunnyCords[0] = myRandom->get_random_number_in_range(rows - 1, 0);
                bunnyCords[1] = rows - 1;
            }
            if (!isCrowded(bunnyCords[0], bunnyCords[1])) {
                break;
            }
        }
        int bounds[2] = {column_capacity(), row_capacity()};
        auto new_bunny = bunny(bounds, bunnyCords);
        bunnies.push_back(&new_bunny);
    }
}

