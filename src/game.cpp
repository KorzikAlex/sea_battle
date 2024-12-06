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

using json = nlohmann::json;

Game::Game(PlayerUnit player, BotUnit bot, GameState game_state): player_(player), bot_(bot), game_state_(game_state)  {

};

void Game::startGame() const {
}

void Game::loadGame(const std::string& file) {
    try {
        this->game_state_.loadGame(file);
    } catch (json::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
    // catch (HashMismatchException& e) {
    //     painter.printException(e);
    // }
}

void Game::saveGame(const std::string& file) {
    this->game_state_.saveGame(file);
}

