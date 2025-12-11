//
// Created by kistj on 12/6/2025.
//
#include "entity_brain.hpp"
#include <algorithm>

int Entity_Brain::max_bunnies() const {
    if (*hard_mode == true) {
        return 8;
    }
    return 4;
}

int Entity_Brain::bunny_chance() const {
    if (*hard_mode == true) {
        return 30;
    }
    return 65;
}

Entity_Brain::Entity_Brain(Player *p, Farmland *f, my_custom_random *r, bool *hard_mode_ptr) {
    my_player = p;
    my_farm = f;
    myRandom = r;
    hard_mode = hard_mode_ptr;
    my_bunnies = &my_farm->myBunniesPtr;
}

bool Entity_Brain::roll_make_bunny() const {
    if (my_bunnies->empty() || my_bunnies->size() < max_bunnies()) {
        if (const int r = myRandom->get_random_number_in_range(1, 100); r >= bunny_chance()) {
            return true;
        }
    }
    return false;
}

bool Entity_Brain::bunnyDePrioritizeLeave(const bunny *b_ptr) {
    if (b_ptr->getAge() > 3) {
        return true;
    }
    return false;
}

bool Entity_Brain::hasBunnies() const {
    if (my_bunnies->empty()) {
        return false;
    }
    return true;
}

void Entity_Brain::random_bunny_move(bunny *b_ptr) const {
    int move_direction = myRandom->get_random_number_in_range(1, 4);
    if (bunnyDePrioritizeLeave(b_ptr)) {
        bool should_move[4] = {true, true, true, true};
        if (b_ptr->getY() == 0) {
            should_move[0] = false;
        }
        if (b_ptr->getY() == my_farm->column_capacity()) {
            should_move[1] = false;
        }
        if (b_ptr->getX() == 0) {
            should_move[2] = false;
        }
        if (b_ptr->getX() == my_farm->row_capacity()) {
            should_move[3] = false;
        }
        int move_anyways = 0;
        while (should_move[move_direction - 1] == false) {
            move_anyways = myRandom->get_random_number_in_range(1, 10);
            if (move_anyways < 8) {
                move_direction = myRandom->get_random_number_in_range(1, 4);
            } else {
                break;
            }
        }
    }
    if (move_direction == 1) {
        b_ptr->move_up();
    } else if (move_direction == 2) {
        b_ptr->move_down();
    } else if (move_direction == 3) {
        b_ptr->move_left();
    } else if (move_direction == 4) {
        b_ptr->move_right();
    }
}

void Entity_Brain::bunny_move(bunny *b_ptr) {
    const char how_move = my_farm->bunny_player_check(b_ptr);
    if (how_move == 'G') { // clear for random move
        random_bunny_move(b_ptr);
        my_farm->bunny_eat(b_ptr);
    } else if (how_move != '0') { // not nullptr
        for (int i = 0; i < 4; i++) {
            if (how_move == 'A') { // player is ABOVE
                b_ptr->move_down();
            } else if (how_move == 'B') { // player is BELOW
                b_ptr->move_up();
            } else if (how_move == 'L') { // player is LEFT
                b_ptr->move_right();
            } else if (how_move == 'R') { // player is RIGHT
                b_ptr->move_left();
            }
            my_farm->bunny_eat(b_ptr);
        }
    }
    if (b_ptr->is_out_of_bounds()) {
        bunny_delete_buffer.push_back(b_ptr);
    }
}

void Entity_Brain::all_bun_eat() const {
    for (const auto &this_bun : *my_bunnies) {
        my_farm->bunny_eat(this_bun);
    }
}


void Entity_Brain::tick_brain() {
    // move all bunnies
    for (const auto &this_bun : *my_bunnies) {
        this_bun->tick();
        bunny_move(this_bun);
    }
    // detect and delete all out of bounds bunnies
    if (!bunny_delete_buffer.empty()) {
        for (int i = bunny_delete_buffer.size() - 1; i >= 0; i--) {
            auto bun_it = std::ranges::find(*my_bunnies, bunny_delete_buffer[i]);
            if (bun_it != my_bunnies->end()) {
                my_bunnies->erase(bun_it);
            }
        }
        bunny_delete_buffer.clear();
    }

    // roll make bunny
    if (roll_make_bunny()) {
        int newBunnyX = 0;
        int newBunnyY = 0;
        my_farm->find_valid_bunny_spawn(newBunnyX, newBunnyY);
        auto new_bunny = new bunny(my_farm->row_capacity(), my_farm->column_capacity(), newBunnyX, newBunnyY);
        my_bunnies->push_back(new_bunny);
        my_farm->bunny_eat(new_bunny);
    }
    all_bun_eat();
}