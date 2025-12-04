#ifndef FARMING_SIMULATOR_V2C_CUPID_HPP
#define FARMING_SIMULATOR_V2C_CUPID_HPP
// this class handles setup for the game,
// and it pairs the classes.

#include "../farm_stuff/farm.hpp"
#include "../farm_stuff/game_printer.hpp"
#include "../entities/player.hpp"
#include "../interactions/inventory.hpp"
#include "../interactions/shop.hpp"
#include "../plots/soil.hpp"
#include "../interactions/items/seeds.hpp"
#include "../random/frandom.hpp"

class cupid {
private:
    inventory playerInventory;
    Soil soil;
    Player player;
    Farm farm;
    Shop shop;
    std::vector<seeds*> seed_unlockables;
    bool seeds_unlocked[3] = {false};
    bool in_menus = false;
    frandom *CupidRandom;

    void unlock_seeds();

    void try_plant();

    void seed_change(GamePrinter *printer, std::string &input);

    void inventory_peek(GamePrinter *printer, std::string &input);

    void legend_peek(GamePrinter *printer, std::string &input);

    void weed_generate();

    void tick_day();

    void water();

public:
    cupid();

    void setRandom(frandom *Crandom);

    void runGame();
};


#endif //FARMING_SIMULATOR_V2C_CUPID_HPP