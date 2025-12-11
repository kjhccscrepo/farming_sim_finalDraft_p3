
#include "farm_game.hpp"
#include "ansi_clear.hpp"
#include "../interactions/items/produce.hpp"
#include "../entities/entity.hpp"
#include "../plots/plant.hpp"
#include "../plots/plants/beet.hpp"
#include "../plots/plants/brussel_sprouts.hpp"
#include "../plots/plants/carrot.hpp"
#include "../plots/plants/lettuce.hpp"
#include "../plots/plants/melon.hpp"
#include "../plots/plants/onion.hpp"
#include "../plots/plants/spinach.hpp"
#include "../plots/plants/zucchini.hpp"
#include "../plots/weeds/weed_classic.hpp"
#include "entity_brain.hpp"

void farm_game::unlock_seeds() {
    if (!seeds_unlocked[0]) {
        if (farm.getDays() > 3) {
            seeds_unlocked[0] = true;
            shop.new_seed(seed_unlockables[0]);
        }
    } else if (!seeds_unlocked[1]) {
        if (farm.getDays() > 7) {
            seeds_unlocked[1] = true;
            shop.new_seed(seed_unlockables[1]);
        }
    } else if (!seeds_unlocked[2]) {
        if (farm.getDays() > 15) {
            seeds_unlocked[2] = true;
            shop.new_seed(seed_unlockables[2]);
        }
    }
}

void farm_game::try_plant() {
    if (playerInventory.is_first_item_plantable()) {
        // a seed has been selected and verified!
        auto *new_plant = new plant(playerInventory.pointer_to_plant());
        farm.plant(player.getX(), player.getY(), new_plant);
        playerInventory.remove_1_seed();
    }
}

void farm_game::seed_change(GamePrinter *printer, std::string &input) {
    playerInventory.sort_me();
    in_menus = true;
    printer->generate_inventory();
    while (in_menus) {
        ansi_clear();
        std::cout << "enter r to cancel, or...\n";
        std::cout << printer->prettyPrint_Inventory() << std::endl;
        std::cout << "Select an appropriate seed by entering its slot in your inventory.";
        std::cout << std::endl;
        std::cin >> input;
        if (input == "r") {
            in_menus = false;
        } else if (isdigit(input.front())) {
            if (std::stoi(input) > 0 && std::stoi(input) <= (playerInventory.mySize())) {
                if (playerInventory.is_X_item_plantable(std::stoi(input) - 1)) {
                    playerInventory.move_item_to_front(std::stoi(input) - 1);
                    in_menus = false;
                }
            } else {
                std::cout << "invalid selection\n";
            }
        }
    }
}

void farm_game::inventory_peek(GamePrinter *printer, std::string &input) {
    playerInventory.sort_me();
    in_menus = true;
    printer->generate_inventory();
    while (in_menus) {
        ansi_clear();
        std::cout << printer->prettyPrint_Inventory() << std::endl;
        std::cin >> input;
        if (input == "r") {
            in_menus = false;
        }
    }
}

void farm_game::legend_peek(GamePrinter *printer, std::string &input) {
    in_menus = true;
    printer->generate_legend();
    while (in_menus) {
        ansi_clear();
        std::cout << printer->prettyPrint_Legend() << std::endl;
        std::cin >> input;
        if (input == "r") {
            in_menus = false;
        }
    }
}

void farm_game::weed_generate() {
    int weeds = 0;
    int r = 0;
    if (hard_mode == true) {
        r = game_random->get_random_number_in_range(1, 100);
        if (r == 100) {
            weeds++;
        }
        if (r >= 75) {
            weeds++;
        }
        if (r >= 55) {
            weeds++;
        }
        if (r >= 40) {
            weeds++;
        }
        if (r >= 25) {
            weeds++;
        }
    } else {
        r = game_random->get_random_number_in_range(-1, 3);
        if (r == -1) {
            r++;
        }
        weeds = r;
    }
    while (weeds != 0) {
        const int x = game_random->get_random_number_in_range(0, farm.row_capacity() - 1);
        const int y = game_random->get_random_number_in_range(0, farm.column_capacity() - 1);
        auto *weed_ptr = new weed_classic();
        farm.plant(x, y, weed_ptr);
        weeds--;
    }
}


void farm_game::tick_day() {
    farm.end_day();
    if (hard_mode_check()) change_toHardMode();
    this->weed_generate();
    B_Brain.tick_brain();
    playerInventory.reset_water();
    unlock_seeds();
    B_Brain.all_bun_eat();
}

void farm_game::water() {
    if (playerInventory.try_water()) {
        farm.water_plot();
    }
}

void farm_game::change_toHardMode() {
        hard_mode = true;
}

bool farm_game::hard_mode_check() const {
    if (farm.getDays() > 10) {
        if (!hard_mode) {
            return true;
        }
    }
    return false;
}

farm_game::farm_game(const int &how_long, const int &how_tall, my_custom_random *random_ptr) :
    game_random(random_ptr),
    farm(how_long, how_tall, &player, random_ptr, &hard_mode),
    B_Brain(&player, &farm, random_ptr, &hard_mode) {
    hard_mode = false;
}


void farm_game::runGame() {
    //plants
    Carrot carrot;
    Melon melon;
    Onion onion;
    Zucchini zucchini;
    Beet beet;
    Brussels_Sprouts brussels_sprouts;
    Lettuce lettuce;
    Spinach spinach;
    // seed setup.
    seeds seeds_Carrot(&carrot);
    seeds seeds_Melon(&melon);
    seeds seeds_Onion(&onion);
    seeds seeds_Zucchini(&zucchini);
    seeds seeds_Beet(&beet);
    seeds seeds_Brussels(&brussels_sprouts);
    seeds seeds_Lettuce(&lettuce);
    seeds seeds_Spinach(&spinach);
    // unlockables
    seed_unlockables.push_back(&seeds_Melon);
    seed_unlockables.push_back(&seeds_Onion);
    seed_unlockables.push_back(&seeds_Zucchini);
    // produce setup.
    produce produce_carrot(&carrot);
    produce produce_melon(&melon);
    produce produce_onion(&onion);
    produce produce_zucchini(&zucchini);
    produce produce_beet(&beet);
    produce produce_brussels(&brussels_sprouts);
    produce produce_lettuce(&lettuce);
    produce produce_spinach(&spinach);
    //class linking
    carrot.link_this_class(&seeds_Carrot, &produce_carrot);
    melon.link_this_class(&seeds_Melon, &produce_melon);
    onion.link_this_class(&seeds_Onion, &produce_onion);
    zucchini.link_this_class(&seeds_Zucchini, &produce_zucchini);
    beet.link_this_class(&seeds_Beet, &produce_beet);
    brussels_sprouts.link_this_class(&seeds_Brussels, &produce_brussels);
    lettuce.link_this_class(&seeds_Lettuce, &produce_lettuce);
    spinach.link_this_class(&seeds_Spinach, &produce_spinach);
    //shop setup
    shop.link(&playerInventory, "Farmer");
    shop.new_seed(&seeds_Carrot);
    shop.new_seed(&seeds_Beet);
    shop.new_seed(&seeds_Lettuce);
    shop.new_seed(&seeds_Spinach);
    shop.new_seed(&seeds_Brussels);
    //initial inventory setup
    playerInventory.add_item_X_times(&seeds_Carrot, 2);
    playerInventory.add_item_X_times(&seeds_Beet, 4);
    playerInventory.add_item_X_times(&seeds_Lettuce, 1);
    playerInventory.add_item_X_times(&seeds_Spinach, 3);
    playerInventory.add_item_X_times(&seeds_Brussels, 7);
    FarmPrinter farm_printer(&farm);
    GamePrinter game_printer(&farm_printer, &playerInventory);
    bool game_in_progress = true;
    std::string player_input;
    while (game_in_progress) {
        ansi_clear();
        std::cout << game_printer.prettyPrint_Game() << std::endl;
        std::cin >> player_input;
        if (player_input == "q") {
            // exits game
            game_in_progress = false;
            std::cout << "\nThank you for playing!\n";
        } else if (player_input == "w") {
            // move up
            farm.move_player_up();
        } else if (player_input == "a") {
            // move left
            farm.move_player_left();
        } else if (player_input == "d") {
            // move right
            farm.move_player_right();
        } else if (player_input == "s") {
            // move down
            farm.move_player_down();
        } else if (player_input == "p") {
            // plant
            if (farm.harvest_val() == -1) { // it is soil and can be planted!
                try_plant();
            }
        } else if (player_input == "h") {
            // harvest
            const int temp_int = farm.harvest_val();
            if (temp_int == 1) { // 1 means it can and will be harvested
                playerInventory.add_item_X_times(farm.current_plot()->seedPointer(), farm.current_plot()->seedDrops());
                playerInventory.add_item_X_times(farm.current_plot()->producePointer(), farm.current_plot()->produceDrops());
                farm.set_soil();
            }
            if (temp_int == -10) { // it's a weed
                farm.set_soil();
            }
        } else if (player_input == "o") {
            // change seed
            seed_change(&game_printer, player_input);
        } else if (player_input == "e") {
            // tick day
            tick_day();
        } else if (player_input == "i") {
            // show inventory
            inventory_peek(&game_printer, player_input);
        } else if (player_input == "l") {
            legend_peek(&game_printer, player_input);
        } else if (player_input == "t") {
            water();
        } else if (player_input == "m") {
            ansi_clear();
            shop.gotoShop();
        }
    }
}
