#pragma once
#include "../include/Board.hpp"
#include "../include/structures.hpp"

#include <fstream>
#include <string>

class Painter {
public:
    void printException(std::exception& e) const;
    void printAbilityName(std::string ability_name) const;
    void printShip(Ship ship) const;
    void printCellValue(Board self, Coord coord) const;
    void printField(Board self) const;
    void printFields(Board self, Board other) const;
};