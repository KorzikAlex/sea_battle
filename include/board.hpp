#ifndef SEABATTLE_BOARD_HPP
#define SEABATTLE_BOARD_HPP

#include <vector>

#include "structures.hpp"

class Board
{
    public:
        explicit Board(int size_x, int size_y);
        void setShip(Coord set_coord);
    private:
        const int size_x_, size_y_;
        std::vector<std::vector<Cell>> field_;
};

#endif // BOARD_HPP
