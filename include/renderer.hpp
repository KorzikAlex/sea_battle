#pragma once

#include <iostream>

#include "board.hpp"

class Renderer {
public:
    Renderer() = default;

    void printBoard(Board board) const;

    void printBoards(Board self_board, Board other_board) const;

    void printException(const std::exception &e) const noexcept;

    void printAbilityName(const std::string &ability_name) const noexcept;

    void printCellValue(Board board, Coord coord) const;

    ~Renderer() = default;
};
