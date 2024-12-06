/**
 * @file game.hpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief Class of game
 * @version 0.2
 * @date 2024-11-15
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include "units.hpp"
#include "game_state.hpp"

/**
 * @class Game
 * @brief Manages the initialization and setup of the game.
 *
 * This class is responsible for parsing command-line arguments, initializing the game board,
 * setting up ships, and managing game abilities.
 */
class Game {
public:
    /**
     * @brief Initializes the game setup.
     *
     * Sets up the game board, initializes ships, and manages game abilities by parsing command-line arguments.
     *
     */
    explicit Game(PlayerUnit player, BotUnit bot, GameState game_state);
    void startGame() const;
private:
    PlayerUnit player_;
    BotUnit bot_;
    GameState game_state_;
};
