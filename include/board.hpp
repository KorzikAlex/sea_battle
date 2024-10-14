#ifndef SEABATTLE_BOARD_HPP
#define SEABATTLE_BOARD_HPP

#include <vector>

#include "ship.hpp"
#include "structures.hpp"


class Board
{
    public:
        explicit Board(int size_x, int size_y);

        ~Board();
        void init(std::vector<Ship*> ships);
        bool setShip(Ship* ship, Coord coord);
        int getCountRows() const;
        int getCountColumns() const;
        bool checkCoord(Coord coord);
    private:
        int size_x_, size_y_;
        std::vector<std::vector<Cell>> field_;
};

#endif // BOARD_HPP
