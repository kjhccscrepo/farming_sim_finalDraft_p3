//
// Created by kistj on 12/3/2025.
//

#ifndef FARMING_SIM_BUNNY_HPP
#define FARMING_SIM_BUNNY_HPP
#include "entity.hpp"


class bunny : public entity {
    int bunny_x;
    int bunny_y;
    int bunny_bound_x;
    int bunny_bound_y;
    std::string bunny_avatar;
public:

    explicit bunny(int bounds_arr[2], const int cords[2]);

    int getX() const override;

    int getY() const override;

    void move_up() override;

    void move_down() override;

    void move_right() override;

    void move_left() override;

    void set_bounds(int xBound, int yBound) override;

    std::string getAvatar() override;

};


#endif //FARMING_SIM_BUNNY_HPP