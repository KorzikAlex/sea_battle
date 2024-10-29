/**
 * @file main.cpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
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

    std::vector<int> ship_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    ShipManager self_manager = ShipManager(ship_sizes);

    std::vector<Coord> self_coords = {
        {0, 0}, {5, 0}, {0, 2}, {4, 2}, {7, 2},
        {0, 4}, {3, 4}, {5, 4}, {7, 4}, {0, 6}
    };

    for (int i = 0; i < self_manager.getShipCount(); ++i)
        self_board.setShip(self_manager.getShip(i), self_coords[i]);

    self_board.printBoard();

    // self_board.printBoardStatus();
    std::cout << "------------------------------" << std::endl;
    self_board.attack(Coord{0, 0});
    self_board.attack(Coord{1, 0});
    self_board.attack(Coord{0, 1});
    self_board.attack(Coord{0, 0});
    self_board.printBoardStatus();
    
    // std::cout << "------------------------------" << std::endl;

    return 0;
}
