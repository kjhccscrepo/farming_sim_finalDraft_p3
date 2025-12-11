//
// Created by kistj on 12/3/2025.
//
#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <string>
class entity {
public:
    virtual ~entity();

    [[nodiscard]] virtual int getX() const = 0;

    [[nodiscard]] virtual int getY() const = 0;

    virtual void move_up() = 0;

    virtual void move_down() = 0;

    virtual void move_right() = 0;

    virtual void move_left() = 0;

    virtual void set_bounds(int xBound, int yBound) = 0;

    virtual std::string getAvatar() = 0;
};
#endif