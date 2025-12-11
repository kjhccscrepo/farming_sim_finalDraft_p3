//
// Created by kistj on 11/18/2025.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "entity.hpp"
#include <string>

class Player final : public entity {
private:
    int current_x;
    int current_y;
    std::string myAvatar;
    int maxX;
    int maxY;

public:
    explicit Player(const std::string &pAvatar);

    Player();

    [[nodiscard]] int getX() const override;

    [[nodiscard]] int getY() const override;

    void move_up() override;

    void move_down() override;

    void move_right() override;

    void move_left() override;

    void set_bounds(int xBound, int yBound) override;

    std::string getAvatar() override;

    void better_start_position();

    void change_avatar(const std::string &n);
};

#endif