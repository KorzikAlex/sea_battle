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

Board::Board(int size_x = 10, int size_y = 10): size_x_(size_x), size_y_(size_y),
                                                board_(this->size_y_, std::vector<Cell>(this->size_x_)) {
};

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
    return this->getCell(coord).isSegmentAt();
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
};

bool Board::setShip(Ship &ship, Coord coord) {
    if (!this->checkCoord(coord)) {
        std::cerr << "Error: Invalid coordinates" << std::endl;
        return false;
    };
    if (ship.isHorizontal()) {
        if (!this->checkCoord(Coord{coord.x + ship.getSize(), coord.y})) {
            std::cerr << "Error: Invalid coordinates" << std::endl;
            return false;
        };
        for (int i = 0; i < ship.getSize(); ++i) {
            if (!this->checkCoordAround(Coord{coord.x + i, coord.y}))
                throw IncorrectShipPositionException("Incorrect ship placement!");
            if (this->isShipAtBoard(Coord{coord.x + i, coord.y}))
                throw IncorrectShipPositionException("Incorrect ship placement!");;
        };
        for (int i = 0; i < ship.getSize(); ++i) this->board_.at(coord.y).at(coord.x + i).segment = ship.getSegment(i);
        return true;
    }
    if (!this->checkCoord(Coord{coord.x, coord.y + ship.getSize()})) {
        std::cerr << "Error: Invalid coordinates" << std::endl;
        return false;
    }
    for (int i = 0; i < ship.getSize(); ++i) {
        if (!this->checkCoordAround(Coord{coord.x, coord.y + i})) return false;
        if (this->isShipAtBoard(Coord{coord.x, coord.y + i})) return false;
    };
    for (int i = 0; i < ship.getSize(); i++) this->board_.at(coord.y + i).at(coord.x).segment = ship.getSegment(i);
    return true;
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


void Board::printBoard() {
    for (int j = 0; j < this->size_y_; ++j) {
        for (int i = 0; i < this->size_x_; ++i) {
            if (this->getCell(Coord{i, j}).isSegmentAt()) {
                if (this->getCell(Coord{i, j}).segment->health == Ship::Segment::SegmentStatus::kWhole)
                    std::cout << "S" << "  ";
                else if (this->getCell(Coord{i, j}).segment->health == Ship::Segment::SegmentStatus::kDamaged)
                    std::cout << "D" << "  ";
                else if (this->getCell(Coord{i, j}).segment->health == Ship::Segment::SegmentStatus::kDestroyed)
                    std::cout << "X" << "  ";
            } else std::cout << "~" << "  ";
        };
        std::cout << std::endl;
    }
};

void Board::printBoardStatus() {
    for (int j = 0; j < this->size_y_; ++j) {
        for (int i = 0; i < this->size_x_; ++i) {
            Cell &board_cell = this->getCell(Coord{i, j});
            if (board_cell.status == Cell::CellVisibilityStatus::kHidden) std::cout << "~" << "  ";
            else if (board_cell.status == Cell::CellVisibilityStatus::kRevealed) {
                if (!board_cell.isSegmentAt()) std::cout << "*" << "  ";
                else {
                    if (board_cell.segment->health == Ship::Segment::SegmentStatus::kWhole)
                        std::cout << "S" << "  ";
                    else if (board_cell.segment->health == Ship::Segment::SegmentStatus::kDamaged)
                        std::cout << "D" << "  ";
                    else if (board_cell.segment->health == Ship::Segment::SegmentStatus::kDestroyed)
                        std::cout << "X" << "  ";
                }
            };
        };
        std::cout << std::endl;
    };
};


Board::~Board() = default;
