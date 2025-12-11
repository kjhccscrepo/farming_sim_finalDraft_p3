//
// Created by kistj on 12/6/2025.
//
#ifndef ENTITY_BRAIN_HPP
#define ENTITY_BRAIN_HPP
#include "../entities/bunny.hpp"
#include "../entities/player.hpp"
#include "../farm_stuff/farmland.hpp"
#include "../random/my_custom_random.hpp"

class Entity_Brain {
private:
    Player *my_player;
    Farmland *my_farm;
    my_custom_random *myRandom;
    std::vector<bunny*> bunny_delete_buffer;
    bool *hard_mode;
    [[nodiscard]] int max_bunnies() const;
    [[nodiscard]] int bunny_chance() const;
    std::vector<bunny*> *my_bunnies;

public:

    explicit Entity_Brain(Player *p, Farmland *f, my_custom_random *r, bool *hard_mode_ptr);

    [[nodiscard]] bool roll_make_bunny() const;

    static bool bunnyDePrioritizeLeave(const bunny *b_ptr) ;

    bool hasBunnies() const;

    void random_bunny_move(bunny *b_ptr) const;

    void bunny_move(bunny *b_ptr);

    void all_bun_eat() const;

    void tick_brain();


};




#endif
