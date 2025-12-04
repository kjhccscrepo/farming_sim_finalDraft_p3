

cmake_minimum_required(VERSION 3.24)

project(farming_sim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.8.1
)
FetchContent_MakeAvailable(Catch2)

add_executable(farming_sim main.cpp
        random/frandom.hpp
        random/real_random.cpp
        entities/entity.hpp
        plots/plants/beet.hpp
        plots/plant.cpp
        plots/plants/brussel_sprouts.hpp
        plots/plants/carrot.hpp
        plots/plants/lettuce.hpp
        plots/plants/melon.hpp
        plots/plants/onion.hpp
        plots/plants/spinach.hpp
        plots/plants/zucchini.hpp
        plots/plot.hpp
        plots/soil.cpp
        interactions/item.hpp
        interactions/inventory.cpp
        plots/weeds/weed_classic.cpp
        interactions/items/seeds.cpp
        interactions/items/produce.cpp
        interactions/shop.cpp
        logic/ansi_clear.hpp
        logic/cupid.cpp
        farm_stuff/farm.cpp
        farm_stuff/farm_printer.cpp
        farm_stuff/game_printer.cpp
        entities/player.cpp
)

add_executable(plants_tests tests/plot_tests/plants_tests.cpp
        plots/plant.cpp
        plots/plants/beet.hpp
        plots/plants/brussel_sprouts.hpp
        plots/plants/carrot.hpp
        plots/plants/lettuce.hpp
        plots/plants/melon.hpp
        plots/plants/onion.hpp
        plots/plants/spinach.hpp
        plots/plants/zucchini.hpp
)

add_executable(soil_test tests/plot_tests/soil_test.cpp
        plots/soil.cpp
        plots/plot.hpp
        interactions/item.hpp
)

add_executable(farm_test tests/farms_test/farm_test.cpp
        farm_stuff/farm.cpp
        farm_stuff/farm_printer.cpp
        interactions/inventory.cpp
        interactions/items/seeds.cpp
        interactions/items/produce.cpp
        interactions/inventory.cpp
        plots/plant.cpp
        plots/plants/carrot.hpp
        plots/soil.cpp
        entities/player.cpp
        entities/bunny.cpp
        plots/weeds/weed_classic.cpp
        random/test_random.cpp
)
add_executable(printer_test tests/farms_test/printer_test.cpp
        farm_stuff/game_printer.cpp
        farm_stuff/farm_printer.cpp
        farm_stuff/farm.cpp
        interactions/inventory.cpp
        interactions/items/seeds.cpp
        interactions/items/produce.cpp
        interactions/inventory.cpp
        plots/plant.cpp
        plots/plants/carrot.hpp
        plots/plants/melon.hpp
        plots/soil.cpp
        entities/player.cpp
        plots/weeds/weed_classic.cpp
)

add_executable(inventory_test tests/farms_test/inventory_test.cpp
        interactions/inventory.cpp
        plots/plot.hpp
        plots/soil.cpp
        interactions/item.hpp
        plots/plant.cpp
        interactions/items/produce.cpp
        interactions/items/seeds.cpp
        plots/plants/carrot.hpp
)
add_executable(item_test tests/farms_test/item_test.cpp
        interactions/item.hpp
        interactions/items/produce.cpp
        interactions/items/seeds.cpp
        plots/plant.cpp
        plots/plants/zucchini.hpp
)
add_executable(player_test tests/farms_test/player_test.cpp
        entities/player.cpp)
add_executable(shop_test tests/farms_test/shop_test.cpp
        interactions/shop.cpp
        interactions/inventory.cpp
        interactions/item.hpp
        interactions/items/produce.cpp
        interactions/items/seeds.cpp
)

target_link_libraries(farming_sim PRIVATE Catch2::Catch2WithMain)
target_link_libraries(plants_tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(soil_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(farm_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(printer_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(player_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(shop_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(item_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(inventory_test PRIVATE Catch2::Catch2WithMain)