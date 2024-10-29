/**
 * @file board.cpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief Implementation of Board Module
 * @version 0.1
 * @date 2024-10-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "board.hpp"
#include "ship.hpp"

Board::Board(int size_x = 10, int size_y = 10) : size_x_(size_x), size_y_(size_y) {
    for (int y = 0; y < size_y_; ++y) {
        std::vector<Cell> row;
        for (int x = 0; x < size_x_; ++x) row.push_back(Cell{CellStatus::kHidden, nullptr});
        this->field_.push_back(row);
    }
}

Board::Board(const Board &other): size_x_(other.size_x_), size_y_(other.size_y_), field_(other.field_) {
};

Board::Board(Board &&other) noexcept: size_x_(other.size_x_), size_y_(other.size_y_), field_(std::move(other.field_)) {
    other.size_x_ = 0;
    other.size_y_ = 0;
    other.field_.clear();
};

Board &Board::operator=(const Board &other) {
    if (this != &other) {
        this->size_x_ = other.size_x_;
        this->size_y_ = other.size_y_;
        this->field_ = other.field_;
    }
    return *this;
};

Board &Board::operator=(Board &&other) noexcept {
    if (this != &other) {
        this->size_x_ = other.size_x_;
        this->size_y_ = other.size_y_;
        this->field_ = std::move(other.field_);

        other.size_x_ = 0;
        other.size_y_ = 0;
    }
    return *this;
};

int Board::getSizeX() const {
    return this->size_x_;
};

int Board::getSizeY() const {
    return this->size_y_;
};

bool Board::checkCoord(Coord coord) const {
    return coord.x >= 0 && coord.x < this->getSizeX() && coord.y >= 0 && coord.y < this->getSizeY();
};

bool Board::checkCoordAround(Coord coord) {
    if (!this->checkCoord(coord)) return false;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (this->checkCoord(Coord{coord.x + i, coord.y + j})) {
                if (this->isShipAtBoard(Coord{coord.x + i, coord.y + j})) return false;
            }
        }
    }
    return true;
};

bool Board::isShipAtBoard(Coord coord) {
    Cell &cell = this->getCell(coord);
    return (cell.segment != nullptr);
};


Cell &Board::getCell(Coord coord) {
    if (this->checkCoord(coord)) return this->field_[coord.y][coord.x];
    throw std::out_of_range("Coordinate out of range");
};

bool Board::attack(Coord coord) {
    if (!this->checkCoord(coord)) {
        std::cout << "Error: Invalid coordinates" << std::endl;
        return false;
    };
    Cell& board_cell = this->getCell(coord);
    if (board_cell.segment) {
        if (board_cell.segment->health == SegmentStatus::kWhole) {
            board_cell.segment->health = SegmentStatus::kDamaged;
        }
        else if (board_cell.segment->health == SegmentStatus::kDamaged) {
            board_cell.segment->health = SegmentStatus::kDestroyed;
        }
    };
    board_cell.status = CellStatus::kRevealed;
    return true;
};

bool Board::setShip(Ship &ship, Coord coord) {
    if (!this->checkCoord(coord)) {
        std::cout << "Error: Invalid coordinates" << std::endl;
        return false;
    };
    if (ship.isHorizontal()) {
        if (!this->checkCoord(Coord{coord.x + ship.getSize(), coord.y})) {
            std::cout << "Error: Invalid coordinates" << std::endl;
            return false;
        };
        for (int i = 0; i < ship.getSize(); ++i) {
            if (!this->checkCoordAround(Coord{coord.x + i, coord.y})) return false;
            if (this->isShipAtBoard(Coord{coord.x + i, coord.y})) return false;
        };
        for (int i = 0; i < ship.getSize(); ++i) this->field_[coord.y][coord.x + i].segment = ship.getSegment(i);
        return true;
    }
    if (!this->checkCoord(Coord{coord.x, coord.y + ship.getSize()})) {
        std::cout << "Error: Invalid coordinates" << std::endl;
        return false;
    }
    for (int i = 0; i < ship.getSize(); ++i) {
        if (!this->checkCoordAround(Coord{coord.x, coord.y + i})) return false;
        if (this->isShipAtBoard(Coord{coord.x, coord.y + i})) return false;
    };
    for (int i = 0; i < ship.getSize(); i++) this->field_[coord.y + i][coord.x].segment = ship.getSegment(i);
    return true;
}

void Board::printBoard() {
    for (int j = 0; j < this->size_y_; ++j) {
        for (int i = 0; i < this->size_x_; ++i) {
            if (this->getCell(Coord{i, j}).segment) std::cout << "S" << "  ";
            else std::cout << "~" << "  ";
        };
        std::cout << std::endl;
    }
};

void Board::printBoardStatus() {
    for (int j = 0; j < this->size_y_; ++j) {
        for (int i = 0; i < this->size_x_; ++i) {
            Cell &cell = this->getCell(Coord{i, j});
            if (cell.status == CellStatus::kHidden) std::cout << "~" << "  ";
            else if (cell.status == CellStatus::kRevealed) {
                if (!cell.segment) std::cout << "*" << "  ";
                else {
                    if (cell.segment->health == SegmentStatus::kWhole) std::cout << "S" << "  ";
                    else if (cell.segment->health == SegmentStatus::kDamaged) std::cout << "D" << "  ";
                    else std::cout << "X" << "  ";
                }
            };
        };
        std::cout << std::endl;
    };
};



Board::~Board() = default;
