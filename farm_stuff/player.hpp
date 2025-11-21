//
// Created by kistj on 11/18/2025.
//

#ifndef FARMING_SIMULATOR_V2C_PLAYER_HPP
#define FARMING_SIMULATOR_V2C_PLAYER_HPP

#include <string>

class Player {
private:
    int current_x;
    int current_y;
    std::string myAvatar;
    int maxX;
    int maxY;

public:
    explicit Player(const std::string &pAvatar);

    Player();

    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;

    void move_up();

    void move_down();

    void move_right();

    void move_left();

    void set_bounds(int xBound, int yBound);

    std::string getAvatar();

    void setUpCheck() const;

    void better_start_position();

    void change_avatar(const std::string &n);
};

#endif //FARMING_SIMULATOR_V2C_PLAYER_HPP