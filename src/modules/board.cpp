#include "board.hpp"

Board::Board(int size_x=10, int size_y=10): size_x_(size_x), size_y_(size_y) {
    for (int i = 0; i < size_y; ++i) {
        std::vector<Cell> cells;
        for (int j = 0; j < size_x; ++j) {
            Cell cell{}
        }
};