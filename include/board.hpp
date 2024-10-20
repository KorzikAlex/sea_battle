#ifndef SEABATTLE_BOARD_HPP
#define SEABATTLE_BOARD_HPP

#include <vector>

#include "ship.hpp"
#include "structures.hpp"


class Board
{
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
        Board (const Board& other);
        /**
         * @brief Move constructor of Board object
         * 
         * @param other 
         */
        Board(Board&& other) noexcept;
        /**
         * @brief Copy assignment of Board object
         * 
         * @param other 
         * @return Board& 
         */
        Board& operator=(const Board& other);
        /**
         * @brief Move assignment of Board object
         * 
         * @param other 
         * @return Board& 
         */
        Board& operator=(Board&& other) noexcept;
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
         * @brief Check if coord in board
         * 
         * @param x 
         * @param y 
         * @return true 
         * @return false 
         */
        bool checkCoord(int x, int y) const;
        /**
         * @brief Get the Cell of Board
         * 
         * @param coord 
         * @return Cell& 
         */
        Cell& getCell(Coord coord);
        /**
         * @brief Get the Cell of Board
         * 
         * @param x 
         * @param y 
         * @return Cell& 
         */
        Cell& getCell(int x, int y);
        /**
         * @brief Check if there are segments of other ships around
         * 
         * @param coord 
         * @return true 
         * @return false 
         */
        bool checkCoordAround(Coord coord);
        /**
         * @brief Check if there are segments of other ships around
         * 
         * @param x 
         * @param y 
         * @return true 
         * @return false 
         */
        bool checkCoordAround(int x, int y);
        /**
         * @brief Attacks by cell position
         * 
         * @param coord 
         * @return true 
         * @return false 
         */
        bool attack(Coord coord);
        /**
         * @brief Attacks by cell position
         * 
         * @param x 
         * @param y 
         * @return true 
         * @return false 
         */
        bool attack(int x, int y);
        /**
         * @brief Set the Ship object on board
         * 
         * @param ship 
         * @param coord 
         * @return true 
         * @return false 
         */
        bool setShip(Ship& ship, Coord coord);
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
