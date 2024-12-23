#include <iostream>

#include "cli_parser.hpp"
#include "game.hpp"

#include "exceptions/invalid_ship_size.hpp"


int main(int argc, char **argv) {
    CLIParser cli_parser(argc, argv);
    Renderer renderer;

    const int kSizeX = cli_parser.getSizeX(), kSizeY = cli_parser.getSizeY();
    Board player_board(kSizeX, kSizeY);
    Board bot_board(kSizeX, kSizeY);

    const std::vector default_ship_sizes({4, 3, 3, 2, 2, 2, 1, 1, 1, 1});
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
    for (std::size_t i = 0; i < default_ship_sizes.size(); ++i) {
        player_board.setShipRandomly(player_ship_manager[i]);
        bot_board.setShipRandomly(bot_ship_manager[i]);
    }

    player_board.revealCells();
    // bot_board.revealCells();
    renderer.printBoards(player_board, bot_board);

    AbilityManager player_ability_manager;
    PlayerUnit player(bot_ship_manager, bot_board, player_ability_manager);
    BotUnit bot(player_ship_manager, player_board);

    GameState game_state(player, bot);
    Game game(player, bot, game_state, renderer);
    game.startGame();

    return EXIT_SUCCESS;
};
