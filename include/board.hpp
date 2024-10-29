/**
 * @file board.hpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief Board module
 * @version 0.1
 * @date 2024-10-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef SEABATTLE_BOARD_HPP
#define SEABATTLE_BOARD_HPP

#include <vector>

#include "ship.hpp"
#include "structures.hpp"


class Board {
public:
    /**
     * @brief Constructor of Board object
     *
     * @param size_x
     * @param size_y
     */
    explicit Board(int size_x, int size_y);

    /**
     * @brief Copy constructor of Board object
     *
     * @param other
     */
    Board(const Board &other);

    /**
     * @brief Move constructor of Board object
     *
     * @param other
     */
    Board(Board &&other) noexcept;

    /**
     * @brief Copy assignment of Board object
     *
     * @param other
     * @return Board&
     */
    Board &operator=(const Board &other);

    /**
     * @brief Move assignment of Board object
     *
     * @param other
     * @return Board&
     */
    Board &operator=(Board &&other) noexcept;

    /**
     * @brief Get the width of Board
     *
     * @return int
     */
    int getSizeX() const;

    /**
     * @brief Get the height of Board
     *
     * @return int
     */
    int getSizeY() const;

    /**
     * @brief Check if coord in board
     *
     * @param coord
     * @return true
     * @return false
     */
    bool checkCoord(Coord coord) const;
    /**
     * @brief Get the Cell of Board
     *
     * @param coord
     * @return Cell&
     */
    Cell &getCell(Coord coord);

    /**
     * @brief Check if there are segments of other ships around
     *
     * @param coord
     * @return true
     * @return false
     */
    bool checkCoordAround(Coord coord);

    /**
     * @brief Check if segment of ship on board
     *
     * @param coord
     * @return true
     * @return false
     */
    bool isShipAtBoard(Coord coord);
    /**
         * @brief Set the Ship object on board
         *
         * @param ship
         * @param coord
         * @return true
         * @return false
         */
    bool setShip(Ship &ship, Coord coord);

    /**
     * @brief Attacks by cell position
     *
     * @param coord
     * @return true
     * @return false
     */
    bool attack(Coord coord);
    /**
     * @brief Print location of ships on board
     *
     */
    void printBoard();

    /**
     * @brief Print how other player see ships on the board
     *
     */
    void printBoardStatus();

    /**
     * @brief Destructor of Board object
     *
     */
    ~Board();

private:
    int size_x_;
    int size_y_;
    std::vector<std::vector<Cell>> field_;
};

#endif // SEABATTLE_BOARD_HPP
