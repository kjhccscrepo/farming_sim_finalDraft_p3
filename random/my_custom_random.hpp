//
// Created by kistj on 12/3/2025.
//
#ifndef MY_CUSTOM_RANDOM_HPP
#define MY_CUSTOM_RANDOM_HPP
class my_custom_random {
public:
    virtual ~my_custom_random();
    virtual int get_random_number() = 0;
    virtual int get_random_number_in_range(const int &minimum, const int &maximum) = 0;
};
#endif