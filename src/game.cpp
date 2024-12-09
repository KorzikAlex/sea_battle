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

#include "game.hpp"

#include "exceptions/no_available_abilities.hpp"

using json = nlohmann::json;

Game::Game(PlayerUnit player, BotUnit bot, GameState game_state): player_(player), bot_(bot),
                                                                  game_state_(game_state), is_bot_win_cond_(false),
                                                                  is_player_win_cond_(false), is_game_end_cond_(false) {
};

void Game::startGame() {
    std::string answer;
    const std::string file = "savefile.json";
    while (!this->is_game_end_cond_) {
        std::string line;
        std::cout << "Push 'p' to play, 'l' to load game, 's' to save game, 'q' to quit. [p/l/s/q] ";
        std::cin >> line;
        if (line.size() == 1) {
            switch (line[0]) {
                case 'p': {
                    // painter.printFields(bot.getField(), player.getField());
                    if (!this->game_state_.getIsAbilityUsed()) {
                        try {
                            this->doPlayerAbility();
                        } catch (NoAvailableAbilitiesException &e) {
                            std::cerr << e.what() << std::endl;
                            break;
                        }
                        catch (OutOfRangeException &e) {
                            std::cerr << e.what() << std::endl;
                            break;
                        }
                        std::cout << "Do you want to quit/load/save the game? y/n" << std::endl;
                        std::cin >> answer;
                        if (answer == "y" || answer == "Y") {
                            break;
                        }
                    }

                    // painter.printFields(bot.getField(), player.getField());
                    doPlayerMove();
                    doBotMove();

                    // для отладки
                    // for (int i = 0; i < 10; i++)
                    //     painter.printShip(player.getShipManager().getShipByIndex(i));

                    // painter.printFields(bot.getField(), player.getField());
                    this->isGameEnd();
                    break;
                }
                case 'l': {
                    std::cout << "Loading the game..." << std::endl;
                    this->loadGame(file);
                    // painter.printFields(bot.getField(), player.getField());
                    break;
                }
                case 's': {
                    std::cout << "Saving the game..." << std::endl;
                    this->saveGame(file);
                    break;
                }
                case 'q': {
                    std::cout << "Quitting the game." << std::endl;
                    this->is_game_end_cond_ = true;
                    break;
                }

                default: {
                    std::cout << "Unknown command." << std::endl;
                    break;
                }
            }
        } else std::cout << "Invalid command." << std::endl;
    }
}

void Game::loadGame(const std::string &file) {
    try {
        this->game_state_.loadGame(file);
    } catch (nlohmann::json::exception &e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
    // catch (HashMismatchException& e) {
    //     painter.printException(e);
    // }
}

void Game::saveGame(const std::string &file) {
    this->game_state_.saveGame(file);
}

void Game::resetRound() {
    std::vector<int> default_ship_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    Board new_bot_board = Board(10, 10);
    ShipManager new_bot_ship_manager = ShipManager(default_ship_sizes);
    for (size_t i = 0; i < default_ship_sizes.size(); i++)
        new_bot_board.setShipRandomly(new_bot_ship_manager[i]);
    this->player_ = PlayerUnit(new_bot_ship_manager, new_bot_board, player_.getAbilityManager());
}

void Game::resetGame() {
    resetRound();

    std::vector<int> default_ship_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    Board new_player_board = Board(10, 10);
    ShipManager new_player_ship_manager = ShipManager(default_ship_sizes);
    for (size_t i = 0; i < default_ship_sizes.size(); i++)
        new_player_board.setShipRandomly(new_player_ship_manager[i]);
    // new_player_board.revealCells();
    this->bot_ = BotUnit(new_player_ship_manager, new_player_board);
}

void Game::isGameEnd() {
    if (!this->is_player_win_cond_ && !this->is_bot_win_cond_) {
        this->is_game_end_cond_ = false;
        return;
    }

    std::cout << "Do you want to continue playing? [Y/n] " << std::endl;
    std::string line;
    std::cin >> line;
    if (line == "n" || line == "N") {
        this->is_game_end_cond_ = true;
        return;
    }

    if (this->is_player_win_cond_) {
        resetRound();
        this->is_player_win_cond_ = false;
        // painter.printFields(this->bot_.getBoard(), this->player_.getBoard());
    }
    if (this->is_bot_win_cond_) {
        resetGame();
        this->is_bot_win_cond_ = false;
        // painter.printFields(this->bot_.getBoard(), this->player_.getBoard());
    }
}

void Game::doPlayerMove() {
    Coord coord;
    int successAttack = false;
    while (true) {
        try {
            std::cin >> coord.x >> coord.y;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw InvalidCoordinateException();
            }

            for (int i = 0; i < this->game_state_.getCurrentDamage(); i++) {
                this->player_.getBoard().attack(coord);
                successAttack = true;
            }
        } catch (InvalidCoordinateException &e) {
            std::cout << e.what() << std::endl;
            continue;
        }
        catch (RevealedCellAttackException &e) {
            if (successAttack) {
                break;
            }
            std::cout << e.what() << std::endl;
            continue;
        }
        catch (OutOfRangeException &e) {
            std::cout << e.what() << std::endl;
            continue;
        }
        break;
    }
    this->game_state_.setCurrentDamage(1);

    Ship *bot_ship = this->player_.getShipManager().getShip(coord);
    if (bot_ship != nullptr && bot_ship->isDestroyed()) {
        this->player_.getBoard().revealCoordinatesAround(bot_ship);
        this->player_.getShipManager().checkShips();
        std::cout << "Ability added." << std::endl;
        this->player_.getAbilityManager().giveRandomAbility();
    }
    if (this->player_.getShipManager().getShipsAlive() == 0) {
        std::cout << "You win!" << std::endl;
        this->is_player_win_cond_ = true;
    }
    this->game_state_.setIsAbilityUsed(false);
}

void Game::doBotMove() {
    Coord coords;
    try {
        coords = this->bot_.getBoard().attackRandomly();
    } catch (MultipleMissesException &e) {
        std::cout << e.what() << std::endl;
        return;
    }

    Ship& selfShip = this->bot_.getShipManager().getShip(coords);
    if (selfShip.isDestroyed()) {
        this->bot_.getBoard().revealCoordinatesAround(selfShip);
        this->bot_.getShipManager().checkShips();
        // this->bot_.getShipManager().setShipsAlive(this->bot_.getShipManager().getShipsAlive() - 1);
    }

    if (this->bot_.getShipManager().getShipsAlive() == 0) {
        std::cout << "You lose!" << std::endl;
        this->is_bot_win_cond_ = true;
    }
}

void Game::doPlayerAbility() {
    std::cout << "You have " << this->player_.getAbilityManager().getAbilityCount() << " abilities available." <<
            std::endl;
    std::cout << "Use random ability? [Y/n] ";

    std::string result;
    std::cin >> result;

    if (result == "y" || result == "Y") {
        Coord coord = {-1, -1};
        AbilityParameters ap(this->player_.getBoard(), this->player_.getShipManager(), coord,
                             this->game_state_.getCurrentDamage());
        this->player_.getAbilityManager().checkIfEmpty();
        std::cout << this->player_.getAbilityManager().returnAbilityName() << std::endl;

        try {
            if (this->player_.getAbilityManager().getCreator(0).isUsingCoordinate()) {
                std::cout << "Give coordinates for ability." << std::endl;
                std::cin >> coord.x >> coord.y;
                ap.coordinate = coord;
            }
            this->player_.getAbilityManager().useAbility(ap);
        } catch (RevealedCellAttackException &e) {
            this->player_.getAbilityManager().popAbility();
        }
    }
    this->game_state_.setIsAbilityUsed(true);
}

Game::~Game() = default;
