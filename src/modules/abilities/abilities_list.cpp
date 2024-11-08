#include <iostream>
#include <random>

#include "abilities/abilities_list.hpp"

DoubleAttack::DoubleAttack(Board &field, Coord coord): board_(field), coord_(coord) {};

Scanner::Scanner(Board &field, Coord coord): board_(field), coord_(coord) {};

RandomAttack::RandomAttack(Board &field): board_(field) {};

void DoubleAttack::realizeAbility() {
    for (int i = 0; i < 2; ++i) this->board_.attack(this->coord_);
};

void Scanner::realizeAbility() {
    for (int j = 0; j <= 1; ++j) {
        for (int i = 0; i <= 1; ++i) {
            if (!board_.checkCoord({this->coord_.x + i, this->coord_.y + j}))
                throw std::invalid_argument("Coordinates");
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
            board_cell.segment->handleDamage();
            std::cout << "Нанесён урон по сегменту в позиции: " << rd_coord.x << " " << rd_coord.y << std::endl;
            break;
        }
    }
};
