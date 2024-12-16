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
#include <locale>

#include "renderer.hpp"
#include "cli_parser.hpp"

#include "board.hpp"
#include "ships/ship_manager.hpp"
#include "abilities/ability_manager.hpp"
#include "units.hpp"
#include "game.hpp"
#include "game_state.hpp"

#include "exceptions/invalid_ship_size.hpp"


/**
 * Main execution entry-point for the program. This function initializes necessary components
 * and starts the main processing loop or lifecycle for the application.
 *
 * @param argc The number of command-line arguments passed to the program.
 * @param argv An array of C-style strings representing the command-line arguments.
 * @return An integer status code where a value of 0 typically indicates successful execution.
 */
int main(int argc, char **argv) {
    setlocale(0, "");

    CLIParser cli_parser(argc, argv);
    Renderer renderer;
    const int kSizeX = cli_parser.getSizeX();
    const int kSizeY = cli_parser.getSizeY();

    Board player_board(kSizeX, kSizeY);
    Board bot_board(kSizeX, kSizeY);

    const std::vector<int> default_ship_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    try {
        for (auto &size: default_ship_sizes)
            if (size < 1 || size > 4)
                throw InvalidShipSizeException();
    } catch (InvalidShipSizeException &e) {
        renderer.printException(e);
        return EXIT_FAILURE;
    }

    ShipManager player_ship_manager(default_ship_sizes);
    ShipManager bot_ship_manager(default_ship_sizes);

    for (size_t i = 0; i < default_ship_sizes.size(); ++i) {
        player_board.setShipRandomly(player_ship_manager[i]);
        bot_board.setShipRandomly(bot_ship_manager[i]);
    }

    player_board.revealCells();
    bot_board.revealCells();
    renderer.printBoards(player_board, bot_board);

    AbilityManager player_ability_manager;

    PlayerUnit player(bot_ship_manager, bot_board, player_ability_manager);
    BotUnit bot(player_ship_manager, player_board);

    GameState game_state(player, bot);
    Game game = Game(player, bot, game_state);
    game.startGame();

    return EXIT_SUCCESS;
};
