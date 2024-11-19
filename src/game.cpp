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
#include <iostream>
#include <SFML/Graphics.hpp>

#include "game.hpp"

#include <exceptions/out_of_range.hpp>

#include "ships/ship_manager.hpp"
#include "abilities/ability_manager.hpp"

#include "exceptions/invalid_ship_size.hpp"
#include "exceptions/no_available_abilities.hpp"
#include "exceptions/incorrect_ship_position.hpp"

const int CELL_SIZE = 30; // Размер одной клетки на поле
const int WINDOW_WIDTH = 750;
const int WINDOW_HEIGHT = 400;

Game::Game(int argc, char **argv): argc_(argc), argv_(argv), parser_(CLIParser(argc_, argv_)) {
};

bool Game::initGame() const {
    const int size_x = this->parser_.getSizeX(); // get size_x from parser
    const int size_y = this->parser_.getSizeY(); // get size_y from parser

    //     Board self_board(size_x, size_y); // create main board
    //     Board enemy_board(size_x, size_y); //create enemy board
    //
    //     std::vector cells1(size_y, std::vector<sf::RectangleShape>(size_x));
    //     std::vector cells2(size_y, std::vector<sf::RectangleShape>(size_x));
    //
    //     // Инициализируем клетки для первого поля
    //     for (int j = 0; j < size_y; ++j) {
    //         for (int i = 0; i < size_x; ++i) {
    //             cells1[j][i].setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    //             cells1[j][i].setOutlineThickness(1);
    //             cells1[j][i].setOutlineColor(sf::Color::Black);
    //             cells1[j][i].setFillColor(sf::Color::Blue);
    //             cells1[j][i].setPosition(50 + i * CELL_SIZE, 50 + j * CELL_SIZE);
    //         }
    //     }
    //
    //     // Инициализируем клетки для второго поля
    //     for (int j = 0; j < size_y; ++j) {
    //         for (int i = 0; i < size_x; ++i) {
    //             cells2[j][i].setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    //             cells2[j][i].setOutlineThickness(1);
    //             cells2[j][i].setOutlineColor(sf::Color::Black);
    //             cells2[j][i].setFillColor(sf::Color::Blue);
    //             cells2[j][i].setPosition(400 + i * CELL_SIZE, 50 + j * CELL_SIZE);
    //         }
    //     }
    //
    //
    //     sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sea battle",
    //                             sf::Style::Titlebar | sf::Style::Close);
    //     window.setFramerateLimit(30);
    //     while (window.isOpen()) {
    //         sf::Event event;
    //         while (window.pollEvent(event)) {
    //             if (event.type == sf::Event::Closed)
    //                 window.close();
    //
    //             // Обработка кликов мыши
    //             if (event.type == sf::Event::MouseButtonPressed) {
    //                 if (event.mouseButton.button == sf::Mouse::Left) {
    //                     sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    //                     int x = (mousePos.x - 50) / CELL_SIZE;
    //                     int y = (mousePos.y - 50) / CELL_SIZE;
    //
    //                     if (x >= 0 && x < size_x && y >= 0 && y < size_y) {
    //                         // self_board.attack({x, y});
    //                         cells1[y][x].setFillColor(sf::Color::Red);
    //                     }
    //
    //                     x = (mousePos.x - 400) / CELL_SIZE;
    //                     y = (mousePos.y - 50) / CELL_SIZE;
    //
    //                     if (x >= 0 && x < size_x && y >= 0 && y < size_y) {
    //                         // enemy_board.attack({x, y});
    //                         cells2[y][x].setFillColor(sf::Color::Red);
    //                     }
    //                 }
    //             }
    //         }
    //
    //         // Очищаем окно
    //         window.clear(sf::Color::White);
    //
    //         // Отрисовываем клетки первого поля
    //         for (int j = 0; j < size_y; ++j) {
    //             for (int i = 0; i < size_x; ++i) {
    //                 window.draw(cells1[j][i]);
    //             }
    //         }
    //
    //         // Отрисовываем клетки второго поля
    //         for (int j = 0; j < size_y; ++j) {
    //             for (int i = 0; i < size_x; ++i) {
    //                 window.draw(cells2[j][i]);
    //             }
    //         }
    //
    //         // Отображаем окно
    //         window.display();
    //     }
    //
    //     return true;
    // }


    Board self_board(size_x, size_y); // create self_board

    const std::vector<int> ship_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1}; // sizes of ships

    try {
        for (auto &size: ship_sizes)
            if (size < 1 || size > 4)
                throw InvalidShipSizeException("Invalid ship size. It must be between 1 and 4.");
    } catch (const InvalidShipSizeException &e) {
        std::cout << e.what() << std::endl;
        return false;
    }

    ShipManager self_manager(ship_sizes); // create self_manager with ships

    std::vector<Coord> self_coords = {
        {0, 0}, {5, 0}, {0, 2}, {4, 2}, {7, 2},
        {0, 4}, {3, 4}, {5, 4}, {7, 4}, {0, 6}
    }; // coordinates of ships
    try {
        for (int i = 0; i < self_manager.getShipCount(); ++i)
            self_board.setShip(self_manager.getShip(i), self_coords.at(i)); // add ships at board
    } catch (const IncorrectShipPositionException &e) {
        std::cout << e.what() << std::endl;
        return false;
    }

    AbilityManager self_ability_manager(self_board); // create self_ability_manager

    self_board.printBoard(); // print positions of ships
    std::cout << "----------------------------" << std::endl;
    while (true) {
        Coord select_coord;
        std::string answer;

        std::cout << "You have " << self_ability_manager.getAbilityCount() << " abilities available." << std::endl;
        std::cout << "Do you want to use random ability [y/n]: ";

        std::cin >> answer;
        if (answer == "Д" || answer == "д" || answer == "Y" || answer == "y") {
            try {
                self_ability_manager.isEmpty();
            } catch (const NoAvailableAbilitiesException &e) {
                std::cout << e.what() << std::endl;
                continue;
            }
            std::string name_of_ability = self_ability_manager.returnAbilityName();
            std::cout << "Ability: " << name_of_ability << std::endl;
            try {
                if (self_ability_manager.returnAbility() == AbilityManager::Abilities::Scanner ||
                    self_ability_manager.returnAbility() == AbilityManager::Abilities::DoubleAttack) {
                    std::cout << "Enter the coordinates: ";
                    std::cin >> select_coord.x >> select_coord.y;
                    self_ability_manager.useAbility(select_coord);
                } else if (self_ability_manager.returnAbility() == AbilityManager::Abilities::RandomAttack) {
                    self_ability_manager.useAbility();
                }
            } catch (OutOfRangeException &e) {
                std::cout << e.what() << std::endl;
                continue;
            }
            if (name_of_ability == "DoubleAttack") {
                try {
                    Ship &ship = self_manager.getShip(self_board.getCell(select_coord).segment);
                    if (ship.isDestroyed()) {
                        self_manager.checkShips();
                        std::cout << "You destroyed ship! One ability added." << std::endl;
                        self_ability_manager.giveRandomAbility();
                    }
                } catch (OutOfRangeException &e) {
                    std::cout << e.what() << std::endl;
                    continue;
                }
            }
        }
        self_board.printBoardStatus();
        while (true) {
            try {
                std::cout << "Enter the coordinates to one attack: ";
                std::cin >> select_coord.x >> select_coord.y;
                self_board.attack(select_coord);
            } catch (OutOfRangeException &e) {
                std::cout << e.what() << std::endl;
                continue;
            }
            break;
        }
        try {
            Ship &ship = self_manager.getShip(self_board.getCell(select_coord).segment);
            if (ship.isDestroyed()) {
                self_manager.checkShips();
                std::cout << "You destroyed ship! One ability added.";
                self_ability_manager.giveRandomAbility();
            }
        } catch (OutOfRangeException &e) {
            std::cout << e.what() << std::endl;
            continue;
        }
        self_board.printBoardStatus();
        if (self_manager.getShipCount() == 0) {
            std::cout << "YOU WIN!!! COOL!!! GREAT!!! EXCELENT!!!" << std::endl;
            break;
        }
    }
    return true;
}
