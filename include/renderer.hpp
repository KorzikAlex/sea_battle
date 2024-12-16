# pragma once

#include "board.hpp"

class Renderer {
public:
    Renderer() = default;

    ~Renderer() = default;

    void printBoard(Board board) const;
    void printBoards(Board self_board, Board other_board) const;
    void printException(std::exception& e) const;

    void printAbilityName(std::string ability_name) const;

    void printCellValue(Board board, Coord coord) const;
    void printInfo() const;
};
