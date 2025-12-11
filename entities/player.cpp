//
// Created by kistj on 11/18/2025.
//

#include "player.hpp"
#include "../plots/weeds/weed_classic.hpp"

Player::Player(const std::string &pAvatar) {
    myAvatar = pAvatar[0];
    current_x = 0;
    current_y = 0;
    maxX = 0;
    maxY = 0;
}

Player::Player() {
    myAvatar = "@";
    current_x = 0;
    current_y = 0;
    maxX = 0;
    maxY = 0;
}

int Player::getX() const {
    return this->current_x;
}

int Player::getY() const {
    return this->current_y;
}

void Player::move_up() {
    if (this->current_y != 0) {
        this->current_y -= 1;
    }
}

void Player::move_down() {
    if (this->current_y != this->maxY - 1) {
        this->current_y += 1;
    }
}

void Player::move_right() {
    if (this->current_x != this->maxX - 1) {
        this->current_x += 1;
    }
}

void Player::move_left() {
    if (this->current_x != 0) {
        this->current_x -= 1;
    }
}

void Player::set_bounds(const int xBound, int yBound) {
    this->maxX = xBound;
    this->maxY = yBound;
}

std::string Player::getAvatar() {
    return this->myAvatar;
}

void Player::better_start_position() {
    this->current_y = maxY - 1;
    this->current_x = (maxX - 1) / 2;
}

void Player::change_avatar(const std::string &n) {
    myAvatar = n[0];
}
