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
#include "cli_parser.hpp"

#include "board.hpp"
#include "ships/ship_manager.hpp"
#include "abilities/ability_manager.hpp"
#include "units.hpp"

#include "exceptions/invalid_ship_size.hpp"
#include "game.hpp"

/**
 * @brief Entry point of the program.
 *
 * This function initializes the game and checks for successful initialization.
 * If initialization fails, it outputs an error message.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Returns EXIT_SUCCESS if the game initializes successfully, otherwise EXIT_FAILURE.
 */
int main(int argc, char **argv) {
    CLIParser cli_parser(argc, argv);
    const int kSizeX = cli_parser.getSizeX();
    const int kSizeY = cli_parser.getSizeY();

    Board player_board(kSizeX, kSizeY);
    Board bot_board(kSizeX, kSizeY);

    const std::vector<int> default_ship_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    try {
        for (auto &size: default_ship_sizes)
            if (size < 1 || size > 4)
                throw InvalidShipSizeException("Invalid ship size. It must be between 1 and 4.");
    } catch (const InvalidShipSizeException &e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    ShipManager player_ship_manager(default_ship_sizes);
    ShipManager bot_ship_manager(default_ship_sizes);

    for (size_t i = 0; i < default_ship_sizes.size(); ++i) bot_board.setShipRandomly(bot_ship_manager[i]);
    // TODO: сделать возможность расстановки кораблей
    AbilityManager player_ability_manager(player_board);

    PlayerUnit player(bot_ship_manager, bot_board, player_ability_manager);
    BotUnit bot(player_ship_manager, player_board);
    GameState game_state(player, bot);
    Game game = Game(player, bot, game_state);
    game.startGame();

    return EXIT_SUCCESS; //return 0
};
