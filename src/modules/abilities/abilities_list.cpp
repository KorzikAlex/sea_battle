/**
 * @file abilities_list.cpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2024-11-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <random>

#include "abilities/abilities_list.hpp"

#include "exceptions/out_of_range.hpp"

DoubleAttack::DoubleAttack(Board &field, Coord coord): board_(field), coord_(coord) {};

Scanner::Scanner(Board &field, Coord coord): board_(field), coord_(coord) {};

RandomAttack::RandomAttack(Board &field): board_(field) {};

void DoubleAttack::realizeAbility() {
    this->board_.attack(this->coord_, 2);
};

void Scanner::realizeAbility() {
    for (int j = 0; j <= 1; ++j) {
        for (int i = 0; i <= 1; ++i) {
            if (!board_.checkCoord({this->coord_.x + i, this->coord_.y + j}))
                throw OutOfRangeException("Coordinate out of range");
            Board::Cell &board_cell = this->board_.getCell({this->coord_.x + i, this->coord_.y + j});
            if (board_cell.isSegmentAt()) {
                std::cout << "Корабль найден на позиции: " << this->coord_.x + i << " " << this->coord_.y + j << std::endl;
                return;
            };
        }
    }
    for (int j = 0; j <= 1; j++)
        for (int i = 0; i <= 1; i++)
            this->board_.getCell({this->coord_.x + i, this->coord_.y + j}).changeStatus();
    std::cout << "Корабль не найден" << std::endl;
};

void RandomAttack::realizeAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, this->board_.getSizeX() - 1);
    std::uniform_int_distribution<> disY(0, this->board_.getSizeY() - 1);
    while (true) {
        Coord rd_coord = {disX(gen), disY(gen)};
        Board::Cell &board_cell = this->board_.getCell(rd_coord);
        if (board_cell.isSegmentAt()) {
            if (board_cell.segment->health != Ship::Segment::SegmentStatus::kDestroyed) {
                board_cell.segment->handleDamage();
                std::cout << "Нанесён урон по сегменту в позиции: " << rd_coord.x << " " << rd_coord.y << std::endl;
            }
            else continue;
            break;
        }
    }
};

Ability::~Ability() = default;
