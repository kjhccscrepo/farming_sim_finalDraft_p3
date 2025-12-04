//
// Created by kistj on 12/3/2025.
//

#include "bunny.hpp"

bunny::bunny(int bounds_arr[2], const int cords[2]) {
    bunny_avatar = "+";
    bunny_x = cords[0];
    bunny_y = cords[1];
    bunny::set_bounds(bounds_arr[0], bounds_arr[1]);
}

int bunny::getX() const {
    return bunny_x;
}

int bunny::getY() const {
    return bunny_y;
}

void bunny::move_up() {
    if (bunny_y != 0) {
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
    if (bunny_x != 0) {
        bunny_x -= 1;
    }
}
void bunny::set_bounds(int xBound, int yBound) {
    this->bunny_bound_x = xBound - 1;
    this->bunny_y = yBound - 1;
}

std::string bunny::getAvatar() {
    return bunny_avatar;
}
