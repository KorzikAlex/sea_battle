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
#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include <random>

#include "ships/ship.hpp"
#include "structures.hpp"

#include "exceptions/out_of_range.hpp"
#include "exceptions/incorrect_ship_position.hpp"
/**
 * @brief Class representing a game board
 */
class Board {
public:
    /**
     * @brief A class that represents a cell on the game board.
     */
    struct Cell {
        /**
         * @brief Enum class representing the visibility status of a cell.
         */
        enum class CellVisibilityStatus {
            kHidden,
            kRevealed
        };

        // TODO: описание добавить
        enum class CellValue : char {
            kShipPart = 'S',
            kDamaged = 'D',
            kDestroyed = 'X',
            kWaterHidden = '~',
            kWaterRevealed = '*'
        };

        /**
         * @brief Status of the cell's visibility.
         *
         * This variable holds the current visibility status of a cell,
         * which can be either hidden or revealed. It is initialized to hidden.
         */
        CellVisibilityStatus status = CellVisibilityStatus::kHidden;
        /**
         * @brief Pointer to a ship segment.
         *
         * Represents the segment of a ship that may be present in the cell.
         * Initialized to nullptr, indicating no ship segment is initially present.
         */
        Ship::Segment *segment = nullptr;

        // TODO: описание добавить
        CellValue value;

        /**
         * @brief Changes the visibility status of the cell.
         *
         * This method toggles the visibility status of the cell from hidden to revealed.
         * If the cell status is currently hidden, it is set to revealed.
         */
        void changeStatus();

        /**
         * @brief Checks whether a ship segment is present in the cell.
         *
         * This method determines if the current cell contains a part of a ship
         * by checking if the `segment` pointer is not null.
         *
         * @return True if there is a ship segment in the cell, false otherwise.
         */
        bool isSegmentAt() const;
    };

    /**
     * @brief Constructs a new Board object with specified dimensions.
     *
     * @param size_x The number of columns in the board. Default is 10.
     * @param size_y The number of rows in the board. Default is 10.
     * @return Board object initialized with the specified or default dimensions.
     */
    explicit Board(int size_x, int size_y);

    /**
     * @brief Copy constructor for the Board class
     *
     * Creates a new Board instance as a copy of another Board instance.
     *
     * @param other The Board instance to copy from.
     * @return A new Board instance with the same properties as the given Board instance.
     */
    Board(const Board &other);

    /**
     * @brief Move constructor for the Board class.
     *
     * This constructor transfers ownership of the resources from another Board object to this one.
     *
     * @param other The Board object to move from. After the move, the state of the other object is reset.
     * @return A newly constructed Board object.
     */
    Board(Board &&other) noexcept;

    /**
     * @brief Assignment operator for the Board class.
     *
     * Copies the content from another Board instance to this instance.
     *
     * @param other The Board instance to assign from.
     * @return A reference to the updated Board instance.
     */
    Board &operator=(const Board &other);

    /**
     * @brief Move assignment operator for the Board class.
     *
     * Transfers ownership of the resources from another Board object to this one.
     *
     * @param other The Board object to move from. After the move, the state of the other object is reset.
     * @return A reference to the updated Board instance.
     */
    Board &operator=(Board &&other) noexcept;

    /**
     * @brief Gets the size of the board in the X dimension.
     * @return The size of the board in the X dimension.
     */
    int getSizeX() const;

    /**
     * @brief Get the Y dimension size of the board.
     * @return The size of the board in the Y dimension.
     */
    int getSizeY() const;

    /**
     * @brief Checks if the given coordinates are within the bounds of the board.
     *
     * @param coord The coordinates to check.
     * @return true if the coordinates are valid, false otherwise.
     */
    bool checkCoord(Coord coord) const;

    /**
     * @brief Retrieves a reference to the cell at the specified coordinates.
     *
     * This method returns a reference to the cell located at the given coordinates on the board.
     * If the coordinates are out of range, an exception is thrown.
     *
     * @param coord The coordinates of the cell to retrieve.
     * @return A reference to the cell at the specified coordinates.
     * @throws std::out_of_range if the coordinates are out of range.
     */
    Cell &getCell(Coord coord);

    /**
     * @brief Verifies if the coordinates around a given coordinate are valid and free of ships.
     *
     * This method checks if the given coordinate is within the bounds of the board and that
     * no ships are placed in the immediate surrounding coordinates (including diagonally).
     *
     * @param coord The coordinate to check.
     * @return true if the coordinate is valid and there are no ships around it, false otherwise.
     */
    bool checkCoordAround(Coord coord);

    /**
     * @brief Checks if there is a ship at the specified coordinates on the board.
     *
     * This method determines whether a ship is present at the given coordinates
     * on the game board. It does so by examining the cell located at the coordinates.
     *
     * @param coord The coordinates to check for the presence of a ship.
     * @return true if a ship is present at the specified coordinates, false otherwise.
     */
    bool isShipAtBoard(Coord coord);

    /**
     * @brief Attempts to place a ship on the board at the specified coordinates.
     *
     * @param ship Reference to a Ship object that is to be placed on the board.
     * @param coord Coordinates on the board where the ship's placement should start.
     * @return True if the ship was successfully placed, false otherwise.
     */
    bool setShip(Ship &ship, Coord coord);

    void setShipRandomly(Ship &ship);

    /**
     * @brief Attacks the cell located at the given coordinates.
     *
     * @param coord The coordinates of the cell to attack.
     */
    void attack(Coord coord, int power = 1);
    // TODO: сделать описание
    void attackRandomly();
    /**
     * @brief Prints the current state of the game board to the standard output
     *
     * This function iterates through the board's cells and prints 'S' for cells
     * containing segments and '~' for empty cells. Each cell is separated by a
     * double space, and rows are separated by newline characters.
     */
    void printBoard();

    /**
     * @brief Prints the current status of the game board.
     *
     * This method iterates over the entire game board and prints the status of each cell.
     * The status includes:
     * - '~' for hidden cells
     * - '*' for revealed empty cells
     * - 'S' for revealed ship segments that are whole
     * - 'D' for revealed ship segments that are damaged
     * - 'X' for revealed ship segments that are destroyed
     */
    void printBoardStatus();

    /**
     * @brief Destructor for the Board class
     */
    ~Board();

private:
    /**
    * @brief Represents the horizontal size of the game board.
    */
    int size_x_;
    /**
     * @brief Height dimension of the board in units
     */
    int size_y_;
    /**
     * @brief 2D vector representing a grid of cells
     */
    std::vector<std::vector<Cell>> board_;
};
