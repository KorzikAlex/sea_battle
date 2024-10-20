#include "board.hpp"

Board::Board(int size_x=10, int size_y=10): size_x_(size_x), size_y_(size_y) {
    std::vector<Cell> row(size_x_, Cell{CellStatus::kHidden});
    this->field_.assign(size_y_, row);
};

Board::Board(const Board& other): size_x_(other.size_x_), size_y_(other.size_y_), field_(other.field_) {};

Board::Board(Board&& other) noexcept: size_x_(other.size_x_), size_y_(other.size_y_), field_(std::move(other.field_)) {
    other.size_x_ = 0;
    other.size_y_ = 0;
    other.field_.clear();
};

Board& Board::operator=(const Board &other) {
    if (this != &other) {
        this->size_x_ = other.size_x_;
        this->size_y_ = other.size_y_;
        this->field_ = other.field_;
    }
    return *this;
};

Board& Board::operator=(Board &&other) noexcept {
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
    return coord.x >= 0 || coord.x < this->getSizeX() || coord.y >= 0 || coord.y < this->getSizeY();
};

bool Board::checkCoord(int x, int y) const {
    return checkCoord(Coord{x, y});
};

bool Board::checkCoordAround(Coord coord) {
    if (!this->checkCoord(coord)) return false;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (this->checkCoord(coord.x + i, coord.y + j)) {
                if (this->getCell(coord).segment) return false;
            }
        }
    }
    return true;
};

bool Board::checkCoordAround(int x, int y) {
    return checkCoordAround(Coord{x, y});
}

Cell& Board::getCell(Coord coord) {
    if (this->checkCoord(coord))
        return this->field_[coord.y][coord.x];
    throw std::out_of_range("Coordinate out of range");
};

Cell& Board::getCell(int x, int y) {
    return this->getCell(Coord{x, y});
}

bool Board::attack(Coord coord) {
    if (!this->checkCoord(coord)) {
        std::cout << "Error: Invalid coordinates" << std::endl;
        return false;
    }
    Cell& board_cell = this->getCell(coord);
    if (board_cell.segment) board_cell.segment->handleDamage();
    board_cell.status = CellStatus::kRevealed;
    return true;
};

bool Board::attack(int x, int y) {
    return this->attack(Coord{x, y});
}

bool Board::setShip(Ship& ship, Coord coord) {
    if (!this->checkCoord(coord)) {
        std::cout << "Error: Invalid coordinates" << std::endl;
        return false;
    }
    if (ship.isHorizontal()) {
        if (!this->checkCoord(coord.x + ship.getSize(), coord.y)) {
            std::cout << "Error: Invalid coordinates" << std::endl;
            return false;
        }

    }
    else if (ship.isVertical()) {
        if (!this->checkCoord(coord.x, coord.y + ship.getSize())) {
            std::cout << "Error: Invalid coordinates" << std::endl;
            return false;
        }
        for (int i = 0; i < ship.getSize(); i++) {};
    }
    return true;
}

Board::~Board() = default;