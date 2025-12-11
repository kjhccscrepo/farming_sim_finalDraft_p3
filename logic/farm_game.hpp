#ifndef FARM_GAME_HPP
#define FARM_GAME_HPP
// this class handles setup for the game,
// and it pairs the classes.

#include "../farm_stuff/farmland.hpp"
#include "../farm_stuff/game_printer.hpp"
#include "../entities/entity.hpp"
#include "../entities/player.hpp"
#include "../interactions/inventory.hpp"
#include "../interactions/shop.hpp"
#include "../plots/soil.hpp"
#include "../interactions/items/seeds.hpp"
#include "../random/my_custom_random.hpp"
#include "entity_brain.hpp"

class farm_game {
private:
    bool hard_mode;
    my_custom_random *game_random;
    Player player;
    Farmland farm;
    Entity_Brain B_Brain;
    inventory playerInventory;
    Soil soil;
    Shop shop;
    std::vector<seeds*> seed_unlockables;
    bool seeds_unlocked[3] = {false};
    bool in_menus = false;

    void unlock_seeds();

    void try_plant();

    void seed_change(GamePrinter *printer, std::string &input);

    void inventory_peek(GamePrinter *printer, std::string &input);

    void legend_peek(GamePrinter *printer, std::string &input);

    void weed_generate();

    void tick_day();

    void water();

    void change_toHardMode();

    bool hard_mode_check() const;

public:

    explicit farm_game(const int &how_long, const int &how_tall, my_custom_random *random_ptr);

    void runGame();
};
#endif