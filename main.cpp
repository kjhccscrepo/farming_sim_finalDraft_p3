
#include "logic/cupid.hpp"
#include "random/real_random.hpp"
int main() {
    real_random game_random;
    cupid game;
    game.setRandom(&game_random);
    game.runGame();
    return 0;
}