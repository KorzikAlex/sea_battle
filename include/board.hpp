#ifndef BOARD_HPP
#define BOARD_HPP

#include "ship.hpp"

class Board {
    private:
        int size_x_, size_y_;
        std::vector<std::vector<FieldCell>> field_;



};

#endif // BOARD_HPP
