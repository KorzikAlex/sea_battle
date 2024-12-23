#include "game.hpp"

Game::Game(const PlayerUnit &player, const BotUnit &bot, const GameState &game_state,
           const Renderer &renderer): player_(player), bot_(bot), game_state_(game_state), renderer_(renderer),
                                      is_player_win_cond_(false), is_bot_win_cond_(false), is_game_end_cond_(false) {
};

void Game::startGame() {
    std::string answer;
    const std::string file_name = "save_file.json";
    while (!this->is_game_end_cond_) {
        std::string line;
        std::cout << "Play(p)\tLoad Game(l)\nSave Game(s)\tQuit(q)\n[p/l/s/q] ";
        std::cin >> line;
        if (line.size() == 1) {
            switch (line[0]) {
                case 'p': {
                    this->renderer_.clear_console();
                    this->renderer_.printBoards(this->bot_.getBoard(),
                                                this->player_.getBoard());
                    try {
                        this->doPlayerAbility();
                    } catch (NoAvailableAbilitiesException &e) {
                        this->renderer_.printException(e);
                        break;
                    }
                    catch (OutOfRangeException &e) {
                        this->renderer_.printException(e);
                        break;
                    }
                    std::cout << "Do you want to save the game? [Y/n] ";
                    std::cin >> answer;
                    if (answer == "y" || answer == "Y") {
                        this->saveGame(file_name);
                        break;
                    }
                    this->renderer_.clear_console();
                    this->renderer_.printBoards(this->bot_.getBoard(), this->player_.getBoard());
                    try {
                        doPlayerMove();
                    } catch (OutOfRangeException &e) {
                        this->renderer_.printException(e);
                    }
                    try {
                        doBotMove();
                    } catch (OutOfRangeException) {
                    }
                    this->isGameEnd();
                    this->renderer_.printBoards(this->bot_.getBoard(), this->player_.getBoard());
                    break;
                }
                case 'l': {
                    this->renderer_.clear_console();
                    std::cout << "Loading the game..." << std::endl;
                    this->loadGame(file_name);
                    this->renderer_.printBoards(this->bot_.getBoard(), this->player_.getBoard());
                    break;
                }
                case 's': {
                    std::cout << "Saving the game..." << std::endl;
                    this->saveGame(file_name);
                    break;
                }
                case 'q': {
                    std::cout << "Quitting the game." << std::endl;
                    this->is_game_end_cond_ = true;
                    break;
                }
                default: {
                    std::cerr << "Unknown command." << std::endl;
                    break;
                }
            }
        } else std::cerr << "Invalid command." << std::endl;
    }
}

void Game::loadGame(const std::string &file) {
    try {
        this->game_state_.loadGame(file);
    } catch (nlohmann::json::exception &e) {
        this->renderer_.printException(e);
    }
    catch (HashMismatchException &e) {
        this->renderer_.printException(e);
    }
}

void Game::saveGame(const std::string &file_name) const {
    this->game_state_.saveGame(file_name);
}

void Game::resetRound() {
    const std::vector default_ship_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    Board new_bot_board(10, 10);
    ShipManager new_bot_ship_manager(default_ship_sizes);
    for (size_t i = 0; i < default_ship_sizes.size(); i++)
        new_bot_board.setShipRandomly(new_bot_ship_manager[i]);
    this->player_ = PlayerUnit(new_bot_ship_manager, new_bot_board, player_.getAbilityManager());
}

void Game::resetGame() {
    resetRound();

    const std::vector default_ship_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    Board new_player_board(10, 10);
    ShipManager new_player_ship_manager(default_ship_sizes);
    for (size_t i = 0; i < default_ship_sizes.size(); i++)
        new_player_board.setShipRandomly(new_player_ship_manager[i]);
    new_player_board.revealCells();
    this->bot_ = BotUnit(new_player_ship_manager, new_player_board);
}

void Game::isGameEnd() {
    if (!this->is_player_win_cond_ && !this->is_bot_win_cond_) {
        this->is_game_end_cond_ = false;
        return;
    }

    std::cout << "Do you want to continue playing? [Y/n] ";
    std::string line;
    std::cin >> line;
    if (line == "n" || line == "N") {
        this->is_game_end_cond_ = true;
        return;
    }
    if (this->is_player_win_cond_) {
        resetRound();
        this->is_player_win_cond_ = false;
        this->renderer_.printBoards(this->bot_.getBoard(), this->player_.getBoard());
    }
    if (this->is_bot_win_cond_) {
        resetGame();
        this->is_bot_win_cond_ = false;
        this->renderer_.printBoards(this->bot_.getBoard(), this->player_.getBoard());
    }
}

void Game::doPlayerMove() {
    Coord coord;
    while (true) {
        try {
            std::cout << "Give coordinates for attack: ";
            std::cin >> coord.x >> coord.y;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw InvalidCoordinateException();
            }
            this->player_.getBoard().attack(coord);
        } catch (InvalidCoordinateException &e) {
            this->renderer_.printException(e);
            continue;
        }
        catch (RevealedCellAttackException &e) {
            this->renderer_.printException(e);
            continue;
        }
        catch (OutOfRangeException &e) {
            this->renderer_.printException(e);
            continue;
        }
        break;
    }

    if (this->player_.getBoard().isSegmentAtCoord(coord)) {
        if (Ship &bot_ship = this->player_.getShipManager().getShip(coord);
            bot_ship.isDestroyed()) {
            this->player_.getBoard().revealCoordinatesAround(bot_ship);
            std::cout << "Ability added." << std::endl;
            this->player_.getAbilityManager().giveRandomAbility();
        }
    }
    if (this->player_.getShipManager().getShipsAlive() == 0) {
        std::cout << "You win!" << std::endl;
        this->is_player_win_cond_ = true;
    }
}

void Game::doBotMove() {
    if (const Coord coord = this->bot_.getBoard().attackRandomly();
        this->bot_.getBoard().isSegmentAtCoord(coord)) {
        if (Ship &player_ship = this->bot_.getShipManager().getShip(coord);
            player_ship.isDestroyed()) this->bot_.getBoard().revealCoordinatesAround(player_ship);
    }
    if (this->bot_.getShipManager().getShipsAlive() == 0) {
        std::cout << "You lose!" << std::endl;
        this->is_bot_win_cond_ = true;
    }
}

void Game::doPlayerAbility() {
    std::cout << "You have " << this->player_.getAbilityManager().getAbilityCount() << " abilities available! ";
    std::cout << "Use random ability? [Y/n] ";
    std::string result;
    std::cin >> result;

    if (result == "y" || result == "Y") {
        Coord coord;
        AbilityParameters ap(this->player_.getBoard(), this->player_.getShipManager(), coord);
        this->player_.getAbilityManager().isEmpty();
        this->renderer_.printAbilityName(this->player_.getAbilityManager().returnAbilityCreator(0).getName());
        try {
            if (this->player_.getAbilityManager().returnAbilityCreator(0).isUsingCoordinate()) {
                std::cout << "Give coordinates for ability [x y]: ";
                std::cin >> coord.x >> coord.y;
                ap.coord = coord;
            }
            this->player_.getAbilityManager().useAbility(ap);
        } catch (RevealedCellAttackException) {
            this->player_.getAbilityManager().popAbility();
        }
    }
}
