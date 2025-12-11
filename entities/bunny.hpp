//
// Created by kistj on 12/3/2025.
//

#ifndef BUNNY_HPP
#define BUNNY_HPP
#include "entity.hpp"
class bunny final : public entity {
    int bunny_x;
    int bunny_y;
    int bunny_bound_x;
    int bunny_bound_y;
    std::string bunny_avatar;
    int age = 0;
public:
    explicit bunny(int xB, int yB, int xCord, int yCord);

    void tick();

    [[nodiscard]] int getAge() const;

    [[nodiscard]] bool is_out_of_bounds() const;

    [[nodiscard]] int getX() const override;

    [[nodiscard]] int getY() const override;

    void move_up() override;

    void move_down() override;

    void move_right() override;

    void move_left() override;

    void set_bounds(int xBound, int yBound) override;

    std::string getAvatar() override;

};

#endif