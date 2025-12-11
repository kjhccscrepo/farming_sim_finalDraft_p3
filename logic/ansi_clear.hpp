//
// Created by kistj on 11/18/2025.
//
#ifndef ANSI_CLEAR_HPP
#define ANSI_CLEAR_HPP
#include <iostream>
inline void ansi_clear() {
    std::cout << "\033[2J\033[H";
}
#endif