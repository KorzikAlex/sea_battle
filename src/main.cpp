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
#include <abilities/ability_manager.hpp>

#include "ships/ship_manager.hpp"
#include "cli_parser.hpp"
#include "structures.hpp"

/**
 * @brief Main function in program
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[]) {
    CLIParser parser(argc, argv);

    int size_x = parser.getSizeX();
    int size_y = parser.getSizeY();

    Board self_board(size_x, size_y);

    const std::vector<int> ship_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    ShipManager self_manager(ship_sizes);

    AbilityManager self_ability_manager(self_board);

    std::vector<Coord> self_coords = {
        {0, 0}, {5, 0}, {0, 2}, {4, 2}, {7, 2},
        {0, 4}, {3, 4}, {5, 4}, {7, 4}, {0, 6}
    };

    for (int i = 0; i < self_manager.getShipCount(); ++i)
        self_board.setShip(self_manager.getShip(i), self_coords.at(i));

    self_board.printBoard();

    std::cout << "----------------------------" << std::endl;
    std::cout << self_ability_manager.returnAbilityName() << std::endl;
    if (self_ability_manager.returnAbility() == AbilityManager::Abilities::Scanner)
        self_ability_manager.useAbility({0, 0});
    else if (self_ability_manager.returnAbility() == AbilityManager::Abilities::RandomAttack)
        self_ability_manager.useAbility();
    else if (self_ability_manager.returnAbility() == AbilityManager::Abilities::DoubleAttack)
        self_ability_manager.useAbility({0, 0});


    // TODO: протестировать работу спосбностей на поле
    // TODO: сканер
    // TODO: двойная атака
    // TODO: случайная атака
    self_board.printBoardStatus();
    return 0;
};
