//
// Created by kistj on 11/18/2025.
//

#ifndef FARMING_SIMULATOR_V2C_PLAYER_HPP
#define FARMING_SIMULATOR_V2C_PLAYER_HPP
#include "entity.hpp"
#include <string>

class Player : public entity {
private:
    int current_x;
    int current_y;
    std::string myAvatar;
    int maxX;
    int maxY;

public:
    explicit Player(const std::string &pAvatar);

    Player();

    int getX() const override;

    int getY() const override;

    void move_up() override;

    void move_down() override;

    void move_right() override;

    void move_left() override;

    void set_bounds(int xBound, int yBound) override;

    std::string getAvatar() override;

    void setUpCheck() const;

    void better_start_position();

    void change_avatar(const std::string &n);
};

#endif //FARMING_SIMULATOR_V2C_PLAYER_HPP