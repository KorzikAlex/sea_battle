#include <iostream>

#include "game.hpp"
#include "ships/ship_manager.hpp"
#include "abilities/ability_manager.hpp"

#include "exceptions/invalid_ship_size.hpp"

Game::Game(int argc, char **argv): argc_(argc), argv_(argv), parser_(CLIParser(argc_, argv_)) {};

bool Game::initGame() const {
    const int size_x = this->parser_.getSizeX();
    const int size_y = this->parser_.getSizeY();

    Board self_board(size_x, size_y);

    const std::vector<int> ship_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    ShipManager self_manager(ship_sizes);
    std::vector<Coord> self_coords = {
        {0, 0}, {5, 0}, {0, 2}, {4, 2}, {7, 2},
        {0, 4}, {3, 4}, {5, 4}, {7, 4}, {0, 6}
    };
    AbilityManager self_ability_manager(self_board);
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
    self_board.printBoardStatus();
    return EXIT_SUCCESS;
}
