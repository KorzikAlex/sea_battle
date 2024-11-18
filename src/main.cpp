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
    if (const Game game(argc, argv); !game.initGame()) { // create object of game and start it
        std::cerr << "Ошибка инициализации игры." << std::endl; // initGame return false
        return EXIT_FAILURE; // return 1
    }
    return EXIT_SUCCESS; //return 0
};
