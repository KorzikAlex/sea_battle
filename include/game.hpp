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
#ifndef SEABATTLE_INCLUDE_GAME_HPP
#define SEABATTLE_INCLUDE_GAME_HPP

#include "cli_parser.hpp"

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
     * @brief Constructs a Game object.
     *
     * Initializes the game by setting up command-line arguments and creating a CLIParser instance.
     *
     * @param argc Number of command-line arguments.
     * @param argv Array of command-line arguments.
    */
    explicit Game(int argc, char **argv);

    /**
     * @brief Initializes the game setup.
     *
     * Sets up the game board, initializes ships, and manages game abilities by parsing command-line arguments.
     *
     * @return bool Returns true if the game initializes successfully, otherwise false.
     */
    bool initGame() const;

private:
    /**
    * @var Game::argc_
    * @brief The number of command-line arguments.
    *
    * This variable stores the total count of command-line arguments passed to the program.
    * It is used to initialize and manage the game setup based on user inputs through the command line.
    */
    int argc_;
    /**
     * @var Game::argv_
     * @brief Array of command-line arguments.
     *
     * This variable stores the command-line arguments passed to the program. It is used in conjunction with argc_ to parse and initialize the game settings using command-line inputs.
     */
    char **argv_;
    /**
     * @var Game::parser_
     * @brief A command-line interface parser instance.
     *
     * This object is responsible for parsing command-line arguments to extract game settings such as board dimensions.
     * It is instantiated using the provided command-line arguments and used throughout the Game class to manage input processing.
     */
    CLIParser parser_;
};

#endif //SEABATTLE_INCLUDE_GAME_HPP
