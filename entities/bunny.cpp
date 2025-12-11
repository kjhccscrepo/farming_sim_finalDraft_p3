//
// Created by kistj on 12/3/2025.
//

#include "bunny.hpp"

bunny::bunny(const int xB, const int yB, const int xCord, const int yCord) {
    bunny_avatar = "+";
    bunny_x = xCord;
    bunny_y = yCord;
    bunny_bound_x = xB;
    bunny_bound_y = yB;
}

void bunny::tick() {
    age++;
}

int bunny::getAge() const {
    return age;
}

bool bunny::is_out_of_bounds() const {
    if (bunny_x == -1 || bunny_y == -1 || bunny_x == bunny_bound_x || bunny_y == bunny_bound_y) {
        return true;
    }
    return false;
}

int bunny::getX() const {
    return bunny_x;
}

int bunny::getY() const {
    return bunny_y;
}

void bunny::move_up() {
    if (bunny_y != -1) {
        bunny_y -= 1;
    }
}

void bunny::move_down() {
    if (bunny_y != bunny_bound_y) {
        bunny_y += 1;
    }
}

void bunny::move_right() {
    if (bunny_x != bunny_bound_x) {
        bunny_x += 1;
    }
}

void bunny::move_left() {
    if (bunny_x != -1) {
        bunny_x -= 1;
    }
}
void bunny::set_bounds(const int xBound, const int yBound) {
    this->bunny_bound_x = xBound;
    this->bunny_y = yBound;
}

std::string bunny::getAvatar() {
    return bunny_avatar;
}
