//
// Created by kistj on 11/18/2025.
//

#include "shop.hpp"
#include "../interactions/item.hpp"
#include <iostream>
#include "../logic/ansi_clear.hpp"

int Shop::has(seeds *seed_ptr) {
    if (seed_ptr == nullptr) {
        return -3;
    }
    if (std::ranges::find(allSeeds, seed_ptr) != allSeeds.end()) {
        for (int position = 0; position < allSeeds.size(); position++) {
            if (this->allSeeds[position]->getMyName() == seed_ptr->getMyName()) {
                return position;
            }
        }
        return -2;
    }
    return -1;
}

int Shop::waterCan() const {
    if (brought_WaterCanUpgrades[0]) {
        if (brought_WaterCanUpgrades[1]) {
            if (brought_WaterCanUpgrades[2]) {
                if (brought_WaterCanUpgrades[3]) {
                    if (brought_WaterCanUpgrades[4]) {
                        return 0;
                    }
                    return waterCanUpgradePrices[4];
                }
                return waterCanUpgradePrices[3];
            }
            return waterCanUpgradePrices[2];
        }
        return waterCanUpgradePrices[1];
    }
    return waterCanUpgradePrices[0];
}

void Shop::waterCanUpgrade_purchase() {
    inventory_ptr->loseMoney(waterCan());
    inventory_ptr->upgrade_water();
    for (int i = 0; i < 5; i++) {
        if (!brought_WaterCanUpgrades[i]) {
            brought_WaterCanUpgrades[i] = true;
            break;
        }
    }
}

Shop::Shop() {
    inventory_ptr = nullptr;
    playerName = "null";
}

void Shop::link(inventory *player_inventory, const std::string &name) {
    inventory_ptr = player_inventory;
    playerName = name;
}

void Shop::new_seed(seeds *seed_ptr) {
    if (seed_ptr != nullptr) {
        if (const int seedPos = has(seed_ptr); seedPos < 0) {
            allSeeds.push_back(seed_ptr);
        } else {
            std::cout << "\nCouldn't add" << seed_ptr->getMyName() << ", is it already in shop?\n";
        }
    } else {
        std::cout << "\ndidnt push nullpointer to shop!\n";
    }

}

std::string Shop::welcome() const {
    return "Hello, " + playerName + ". Welcome to the shop!";
}

std::string Shop::menu_options() {
    std::string menu = "\n1) Buy new Things"
            "\n2) Sell Produce/Seeds"
            "\n3) Return to Farm";
    return menu;
}

std::string Shop::print_Player_money() const {
    return "(You have, " + inventory_ptr->printMoney() + ")\n";
}

std::string Shop::buy_options() const {
    std::stringstream buy_opt;
    buy_opt << "Here is what I can sell to you.\n";
    int i = 0;
    for (i = 0; i < allSeeds.size(); i++) {
        buy_opt << (i + 1) << ") ";
        buy_opt << allSeeds[i]->getMyName();
        buy_opt << ":\t$";
        buy_opt << allSeeds[i]->getCost();
        buy_opt << "\n";
    }
    if (waterCan() != 0) {
        buy_opt << (i + 1) << ") ";
        buy_opt << "Better Watering Can:\t $";
        buy_opt << waterCan();
        buy_opt << "\n";
    }
    return buy_opt.str();
}


std::string Shop::sell_options() const {
    std::stringstream sell_opt;
    sell_opt << "Here is what I'll can buy from you you.\n";
    sell_opt << inventory_ptr->sell_stream();
    return sell_opt.str();
}

std::string Shop::goodbye() {
    return "Thanks for stopping bye!\n";
}

void Shop::gotoShop() {
    bool atShop = true;
    std::cin.clear();
    std::cin.ignore();
    std::string userInput;
    ansi_clear();
    std::cout << print_Player_money() << welcome() << std::endl;
    while (atShop) {
        while (true) {
            std::cout << menu_options() << std::endl;
            std::getline(std::cin, userInput);
            if (!userInput.empty()) {
                if (std::isdigit(userInput[0])) {
                    if (userInput == "1" || userInput == "2" || userInput == "3") {
                        break;
                    }
                }
            }
            std::cout << "Invalid option, enter a valid input!\n";
        }
        if (userInput == "1") {
            int choice = -1;
            bool purchase_seed = false;
            while (true) {
                std::cout << print_Player_money() << buy_options() << std::endl;
                std::cout << "r) exit\n";
                std::getline(std::cin, userInput);
                if (!userInput.empty()) {
                    if (userInput == "r") {
                        break;
                    }
                    if (waterCan() != 0) {
                        if (std::stoi(userInput) == allSeeds.size() + 1) {
                            if (waterCan() <= inventory_ptr->getMoney()) {
                                std::cout << "Brought a better watering can for $";
                                std::cout << waterCan() << ".\n";
                                waterCanUpgrade_purchase();
                            } else {
                                std::cout << "You don't have enough money!\n";
                            }
                            break;
                        }
                    }
                    if (const int temp = std::stoi(userInput); temp >= 1 && temp <= allSeeds.size()) {
                        choice = temp - 1;
                        purchase_seed = true;
                        break;
                    }
                }
                std::cout << "Invalid option, enter a valid input!\n";
            }
            while (purchase_seed) {
                std::cout << "How many " + allSeeds[choice]->getMyName() + " do you want to buy?\n";
                std::cout << print_Player_money();
                std::cout << "\nAmount:\t ";
                std::getline(std::cin, userInput);
                if (!userInput.empty()) {
                    bool cont = true;

                    for (int i = 0; i < userInput.size(); i++) {
                        if (!std::isdigit(userInput[i])) {
                            cont = false;
                        }
                    }
                    if (cont) {
                        int amount = std::stoi(userInput);
                        std::cout << inventory_ptr->buy_attempt(allSeeds[choice], amount);
                        break;
                    }
                }
            }
        }
        if (userInput == "2") {
            inventory_ptr->sort_me();
            int choice = -1;
            while (true) {
                std::cout << sell_options() << std::endl;
                std::cout << "r) exit\n";
                std::getline(std::cin, userInput);
                if (!userInput.empty()) {
                    if (userInput == "r") {
                        break;
                    }
                    if (const int temp = std::stoi(userInput);
                        temp >= 1 && temp <= inventory_ptr->how_many_types_of_things()) {
                        choice = temp - 1;
                        break;
                    }
                }
                std::cout << "Invalid option, enter a valid input!\n";
            }
            while (true) {
                if (userInput == "r") {
                    break;
                }
                std::cout << "How many " + inventory_ptr->getNameOfItemX(choice) + " do you want to sell?\n";
                std::cout << "(You have, " + std::to_string(inventory_ptr->getAmountOfItemX(choice)) + ")";
                std::cout << "\nAmount:\t ";
                std::getline(std::cin, userInput);
                if (!userInput.empty()) {
                    bool cont = true;
                    for (int i = 0; i < userInput.size(); i++) {
                        if (!std::isdigit(userInput[i])) {
                            cont = false;
                        }
                    }
                    if (cont) {
                        int amount = std::stoi(userInput);
                        std::cout << inventory_ptr->sell_attempt(choice, amount);
                        break;
                    }
                }
            }
        }
        if (userInput == "3") {
            atShop = false;
        }
    }
    std::cout << goodbye() << std::endl;
}
