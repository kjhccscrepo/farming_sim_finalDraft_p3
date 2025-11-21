#ifndef FARMING_SIMULATOR_V2C_SHOP_HPP
#define FARMING_SIMULATOR_V2C_SHOP_HPP

#include "inventory.hpp"
#include "item.hpp"
#include "items/seeds.hpp"

class Shop {
    std::vector<seeds *> allSeeds;
    inventory *inventory_ptr;
    std::string playerName;

    int has(seeds *seed_ptr);

    int waterCanUpgradePrices[5] = {50, 120, 300, 760, 2146};
    bool broughtWUPS[5] = {false};

    [[nodiscard]] int waterCan() const;

    void waterCanUpgrade_purchase();

public:
    Shop();

    void link(inventory *player_inventory, const std::string &name);

    void new_seed(seeds *seed_ptr);

    [[nodiscard]] std::string welcome() const;

    static std::string menu_options();

    [[nodiscard]] std::string buy_options() const;

    [[nodiscard]] std::string sell_options() const;

    static std::string goodbye();

    void gotoShop();
};

#endif //FARMING_SIMULATOR_V2C_SHOP_HPP