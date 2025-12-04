//
// Created by kistj on 12/3/2025.
//
#ifndef FARMING_SIM_ENTITY_HPP
#define FARMING_SIM_ENTITY_HPP
#include <string>

class entity {
public:
    virtual ~entity() = default;

    virtual int getX() const;

    virtual int getY() const;

    virtual void move_up();

    virtual void move_down();

    virtual void move_right();

    virtual void move_left();

    virtual void set_bounds(int xBound, int yBound);

    virtual std::string getAvatar();

};
#endif