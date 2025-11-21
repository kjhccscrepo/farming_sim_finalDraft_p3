
#include "farm.hpp"
#include "../plots/soil.hpp"
#include "../plots/weeds/weed_classic.hpp"
#include <random>

Farm::Farm(const int ini_rows, const int ini_columns) {
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
                if (const int r = (rand() % 9); r > 4) {
                    const auto weed = new weed_classic();
                    plant(xBuffer[i] - 1, yBuffer[i], weed);
                }
            }
            if (yBuffer[i] > 0) {
                if (const int r = (rand() % 9); r > 4) {
                    const auto weed = new weed_classic();
                    plant(xBuffer[i], yBuffer[i] - 1, weed);
                }
            }
            if (xBuffer[i] < xMax - 1) {
                if (const int r = (rand() % 9); r > 4) {
                    const auto weed = new weed_classic();
                    plant(xBuffer[i] + 1, yBuffer[i], weed);
                }
            }
            if (yBuffer[i] < yMax - 1) {
                if (const int r = (rand() % 9); r > 4) {
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
    plots[myPlayer->getX()][myPlayer->getY()]->water();
}

Plot *Farm::current_plot() const {
    return plots[myPlayer->getX()][myPlayer->getY()];
}
