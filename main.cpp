
#include "logic/farm_game.hpp"
#include "random/real_random.hpp"
int main() {
    real_random game_random;
    farm_game game(17, 11, &game_random);
    game.runGame();
    return 0;
}