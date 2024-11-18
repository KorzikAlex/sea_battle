/**
 * @file game.cpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief Game class implementation file
 * @version 0.1
 * @date 2024-11-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>

#include "game.hpp"

#include <exceptions/attack_out_of_range.hpp>

#include "ships/ship_manager.hpp"
#include "abilities/ability_manager.hpp"

#include "exceptions/invalid_ship_size.hpp"
#include "exceptions/no_available_abilities.hpp"
#include "exceptions/incorrect_ship_position.hpp"

Game::Game(int argc, char **argv): argc_(argc), argv_(argv), parser_(CLIParser(argc_, argv_)) {
};

bool Game::initGame() const {
    const int size_x = this->parser_.getSizeX(); // get size_x from parser
    const int size_y = this->parser_.getSizeY(); // get size_y from parser

    Board self_board(size_x, size_y); // create self_board

    const std::vector<int> ship_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1}; // sizes of ships

    try {
        for (auto &size: ship_sizes)
            if (size < 1 || size > 4)
                throw InvalidShipSizeException("Invalid ship size. It must be between 1 and 4.");
    } catch (const InvalidShipSizeException &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    ShipManager self_manager(ship_sizes); // create self_manager with ships

    std::vector<Coord> self_coords = {
        {0, 0}, {5, 0}, {0, 2}, {4, 2}, {7, 2},
        {0, 4}, {3, 4}, {5, 4}, {7, 4}, {0, 6}
    }; // coordinates of ships
    try {
        for (int i = 0; i < self_manager.getShipCount(); ++i)
            self_board.setShip(self_manager.getShip(i), self_coords.at(i)); // add ships at board
    } catch (const IncorrectShipPositionException &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    AbilityManager self_ability_manager(self_board); // create self_ability_manager

    self_board.printBoard(); // print positions of ships
    std::cout << "----------------------------" << std::endl;
    while (true) {
        Coord select_coord;
        std::string answer;
        std::cout << "You have " << self_ability_manager.getAbilityCount() << " abilities available." << std::endl;
        std::cout << "Do you want to use random ability [y/n]: ";
        std::cin >> answer;
        if (answer == "Д" || answer == "д" || answer == "Y" || answer == "y") {
            try {
                self_ability_manager.isEmpty();
            } catch (const NoAvailableAbilitiesException &e) {
                std::cout << e.what() << std::endl;
                continue;
            }
            std::cout << "Ability: " << self_ability_manager.returnAbilityName() << std::endl;
            if (self_ability_manager.returnAbility() == AbilityManager::Abilities::Scanner ||
                self_ability_manager.returnAbility() == AbilityManager::Abilities::DoubleAttack) {
                std::cout << "Enter the coordinates: ";
                std::cin >> select_coord.x >> select_coord.y;
                self_ability_manager.useAbility(select_coord);
            } else if (self_ability_manager.returnAbility() == AbilityManager::Abilities::RandomAttack) {
                self_ability_manager.useAbility();
            }
            self_board.printBoardStatus();
        }

        while (true) {
            try {
                std::cin >> select_coord.x >> select_coord.y;
                self_board.attack(select_coord);
            } catch (AttackOutOfRangeException &e) {
                std::cerr << e.what() << std::endl;
                continue;
            }
            break;
        }
    }
    return true;
}
