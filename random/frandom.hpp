//
// Created by kistj on 12/3/2025.
//
#ifndef FARMING_SIM_FRANDOM_HPP
#define FARMING_SIM_FRANDOM_HPP
class frandom {
public:
    virtual ~frandom() = default;
    virtual int get_random_number();
    virtual int get_random_number_in_range(const int &minimum, const int &maximum);
};
#endif