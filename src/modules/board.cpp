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

void Board::Cell::changeStatus() {
    if (this->status == CellVisibilityStatus::kHidden) this->status = CellVisibilityStatus::kRevealed;
}

bool Board::Cell::isSegmentAt() const {
    return this->segment != nullptr;
}

Board::Board(int size_x = 10, int size_y = 10): size_x_(size_x), size_y_(size_y) {
    for (int i = 0; i < this->size_y_; i++) {
        std::vector<Cell> row;
        for (int j = 0; j < this->size_x_; j++)
            row.push_back(Cell{Cell::CellVisibilityStatus::kHidden, nullptr, Cell::CellValue::kWaterHidden});
        this->board_.push_back(row);
    }
}

Board::Board(const Board &other): size_x_(other.size_x_), size_y_(other.size_y_), board_(other.board_) {
};

Board::Board(Board &&other) noexcept: size_x_(other.size_x_), size_y_(other.size_y_), board_(std::move(other.board_)) {
    other.size_x_ = 0;
    other.size_y_ = 0;
    other.board_.clear();
};

Board &Board::operator=(const Board &other) {
    if (this != &other) {
        this->size_x_ = other.size_x_;
        this->size_y_ = other.size_y_;
        this->board_ = other.board_;
    }
    return *this;
};

Board &Board::operator=(Board &&other) noexcept {
    if (this != &other) {
        this->size_x_ = other.size_x_;
        this->size_y_ = other.size_y_;
        this->board_ = std::move(other.board_);

        other.size_x_ = 0;
        other.size_y_ = 0;
    }
    return *this;
};

int Board::getSizeX() const {
    return this->size_x_; // get size_x of board
};

int Board::getSizeY() const {
    return this->size_y_; // get size_y of board
};

bool Board::checkCoord(Coord coord) const {
    return coord.x >= 0 && coord.x < this->getSizeX() && coord.y >= 0 && coord.y < this->getSizeY();
};

bool Board::checkCoordAround(Coord coord) {
    if (!this->checkCoord(coord)) return false;
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (this->checkCoord(Coord{coord.x + i, coord.y + j}))
                if (this->isShipAtBoard(Coord{coord.x + i, coord.y + j})) return false;
    return true;
};

bool Board::isShipAtBoard(Coord coord) {
    Cell cell = this->getCell(coord);
    return (cell.value == Cell::CellValue::kShipPart ||
            cell.value == Cell::CellValue::kDamaged ||
            cell.value == Cell::CellValue::kDestroyed);
};

void Board::revealCoordinatesAround(Ship &ship) {
    for (int k = 0; k < ship.getSize(); ++k) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (!this->checkCoord(
                    {ship.getSegment(k)->segment_coord.x + i, ship.getSegment(k)->segment_coord.y + j})) {
                    Cell &board_cell = this->board_[ship.getSegment(k)->segment_coord.y + j]
                            [ship.getSegment(k)->segment_coord.x + i];
                    if (board_cell.value != Cell::CellValue::kWaterHidden) continue;
                    board_cell.status = Cell::CellVisibilityStatus::kRevealed;
                    board_cell.value = Cell::CellValue::kWaterRevealed;
                }
            }
        }
    }
};

Board::Cell &Board::getCell(Coord coord) {
    if (this->checkCoord(coord)) return this->board_.at(coord.y).at(coord.x);
    throw OutOfRangeException("Coordinate out of range");
};

void Board::attack(Coord coord, int power) {
    if (!this->checkCoord(coord)) throw OutOfRangeException("Coordinate out of range");
    Cell &board_cell = this->getCell(coord);
    if (board_cell.isSegmentAt()) board_cell.segment->handleDamage(power);
    board_cell.changeStatus();
    switch (board_cell.value) {
        case Cell::CellValue::kWaterHidden: {
            board_cell.value = Cell::CellValue::kWaterRevealed;
            break;
        }
        case Cell::CellValue::kShipPart: {
            board_cell.value = Cell::CellValue::kDamaged;
            break;
        }
        case Cell::CellValue::kDamaged: {
            board_cell.value = Cell::CellValue::kDestroyed;
            break;
        }
        default: {
            throw RevealedCellAttackException("Cell is already revealed!");
            break;
        }
    }
};

Coord Board::attackRandomly() {
    std::random_device rd;
    std::uniform_int_distribution<> disX(0, this->getSizeX() - 1);
    std::uniform_int_distribution<> disY(0, this->getSizeY() - 1);
    std::mt19937 gen(rd());

    int j = 0;
    while (true) {
        int randomX = disX(gen);
        int randomY = disY(gen);

        try {
            if (this->checkCoord({randomX, randomY})) {
                this->attack({randomX, randomY});
                return {randomX, randomY};
            }
        } catch (RevealedCellAttackException &e) {
        }
        catch (OutOfRangeException &e) {
        }
    }
}


void Board::setShip(Ship &ship, Coord coord) {
    if (!this->checkCoord(coord))
        throw IncorrectShipPositionException("Invalid coordinates!");
    if (ship.isHorizontal()) {
        if (!this->checkCoord(Coord{coord.x + ship.getSize(), coord.y}))
            throw IncorrectShipPositionException("Invalid coordinates!");
        for (int i = 0; i < ship.getSize(); ++i) {
            if (!this->checkCoordAround(Coord{coord.x + i, coord.y}))
                throw IncorrectShipPositionException("Incorrect ship placement!");
            if (this->isShipAtBoard(Coord{coord.x + i, coord.y}))
                throw IncorrectShipPositionException("Incorrect ship placement!");
        };
        for (int i = 0; i < ship.getSize(); ++i) {
            this->board_.at(coord.y).at(coord.x + i).segment = ship.getSegment(i);
            this->board_.at(coord.y).at(coord.x + i).value = Cell::CellValue::kShipPart;
        }
        return;
    }
    if (!this->checkCoord(Coord{coord.x, coord.y + ship.getSize()}))
        throw IncorrectShipPositionException("Invalid coordinates!");
    for (int i = 0; i < ship.getSize(); ++i) {
        if (!this->checkCoordAround(Coord{coord.x, coord.y + i}))
            throw IncorrectShipPositionException("Incorrect ship placement!");
        if (this->isShipAtBoard(Coord{coord.x, coord.y + i}))
            throw IncorrectShipPositionException("Incorrect ship placement!");
    }
    for (int i = 0; i < ship.getSize(); ++i) {
        this->board_.at(coord.y + i).at(coord.x).segment = ship.getSegment(i);
        this->board_.at(coord.y + i).at(coord.x).value = Cell::CellValue::kShipPart;
    }
}

void Board::setShipRandomly(Ship &ship) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_x(0, this->getSizeX() - 1);
    std::uniform_int_distribution<> dis_y(0, this->getSizeY() - 1);
    std::uniform_int_distribution<> dis_orientation(0, 1);

    while (true) {
        int random_x = dis_x(gen);
        int random_y = dis_y(gen);
        int rand_orientation = dis_orientation(gen);

        if (rand_orientation == 1) ship.setOrientation(Ship::Orientation::kVertical);
        try {
            this->setShip(ship, {random_x, random_y});
            break;
        } catch (IncorrectShipPositionException &e) {
        }
    }
}

void Board::revealCells() {
    for (auto &row: this->board_) for (auto &cell: row) cell.changeStatus();
}

Board::~Board() = default;
