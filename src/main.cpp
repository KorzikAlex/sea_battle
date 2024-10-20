/**
 * @file main.cpp
 * @author Korzik (alek.korshkov@yandex.ru)
 * @brief Main program file
 * @version 0.1
 * @date 2024-10-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
// #include <SFML/Graphics.hpp>

#include "structures.hpp"
#include "ship.hpp"
#include "shipmanager.hpp"
#include "board.hpp"

/**
 * @brief Main function in program
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[]) {
    Board self_board = Board(10, 10);
    Board enemy_board = Board(10, 10);

    std::vector<int> ship_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    ShipManager self_manager = ShipManager(ship_sizes);
    ShipManager enemy_manager = ShipManager(ship_sizes);

    // self_board.init(self_manager.getShips());
    // enemy_board.init(self_manager.getShips());

    return 0;
}
