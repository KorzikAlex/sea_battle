#include "board.hpp"

void Board::Cell::changeStatus() noexcept {
    if (this->status == CellVisibilityStatus::kHidden) this->status = CellVisibilityStatus::kRevealed;
}

bool Board::Cell::isSegmentAt() const noexcept {
    return this->segment != nullptr;
}

Board::Board(const int size_x = 10, const int size_y = 10): size_x_(size_x), size_y_(size_y) {
    for (int i = 0; i < this->size_y_; i++) {
        std::vector<Cell> row;
        for (int j = 0; j < this->size_x_; j++)
            row.push_back(Cell{Cell::CellVisibilityStatus::kHidden, nullptr, Cell::CellValue::kWaterHidden});
        this->board_.push_back(row);
    }
}

Board::Board(const Board &other) noexcept: size_x_(other.size_x_), size_y_(other.size_y_), board_(other.board_) {
}

Board::Board(Board &&other) noexcept: size_x_(other.size_x_), size_y_(other.size_y_), board_(std::move(other.board_)) {
    other.size_x_ = 0;
    other.size_y_ = 0;
    other.board_.clear();
}

Board &Board::operator=(const Board &other) noexcept {
    if (this != &other) {
        this->size_x_ = other.size_x_;
        this->size_y_ = other.size_y_;
        this->board_ = other.board_;
    }
    return *this;
}

Board &Board::operator=(Board &&other) noexcept {
    if (this != &other) {
        this->size_x_ = other.size_x_;
        this->size_y_ = other.size_y_;
        this->board_ = std::move(other.board_);

        other.size_x_ = 0;
        other.size_y_ = 0;
        other.board_.clear();
    }
    return *this;
}

int Board::getSizeX() const noexcept {
    return this->size_x_;
}

int Board::getSizeY() const noexcept {
    return this->size_y_;
}

bool Board::checkCoord(const Coord coord) const noexcept {
    return coord.x >= 0 && coord.x < this->getSizeX() && coord.y >= 0 && coord.y < this->getSizeY();
}

bool Board::checkCoordAround(const Coord coord) noexcept {
    if (!this->checkCoord(coord)) return false;
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (this->checkCoord(Coord{coord.x + i, coord.y + j}))
                if (this->isSegmentAtCoord(Coord{coord.x + i, coord.y + j})) return false;
    return true;
}

bool Board::isSegmentAtCoord(const Coord coord) noexcept {
    return this->getCell(coord).isSegmentAt();
    // const Cell cell = this->getCell(coord);
    // return (cell.value == Cell::CellValue::kShipPart ||
    //         cell.value == Cell::CellValue::kDamaged ||
    //         cell.value == Cell::CellValue::kDestroyed);
}

void Board::revealCoordinatesAround(Ship &ship) {
    for (int k = 0; k < ship.getSize(); ++k)
        for (int i = -1; i <= 1; ++i)
            for (int j = -1; j <= 1; ++j) {
                const Ship::Segment *ship_segment = ship.getSegment(k);
                if (const Coord segment_coord({
                    ship_segment->segment_coord.x + i,
                    ship_segment->segment_coord.y + j
                }); !this->checkCoord(segment_coord)) {
                    Cell &board_cell = this->getCell(Coord{segment_coord});
                    if (board_cell.value != Cell::CellValue::kWaterHidden) continue;
                    board_cell.status = Cell::CellVisibilityStatus::kRevealed;
                    board_cell.value = Cell::CellValue::kWaterRevealed;
                }
            }
}

Board::Cell &Board::getCell(const Coord coord) {
    if (this->checkCoord(coord)) return this->board_.at(coord.y).at(coord.x);
    throw OutOfRangeException();
}

void Board::attack(const Coord coord, const int power) {
    if (!this->checkCoord(coord)) throw OutOfRangeException();
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
        default: throw RevealedCellAttackException();
    }
}

Coord Board::attackRandomly() {
    std::random_device rd;
    std::uniform_int_distribution disX(0, this->getSizeX() - 1);
    std::uniform_int_distribution disY(0, this->getSizeY() - 1);
    std::mt19937 gen(rd());

    while (true) {
        try {
            if (const Coord attack_coord({disX(gen), disY(gen)}); this->checkCoord(attack_coord)) {
                this->attack(attack_coord);
                return attack_coord;
            }
        } catch (RevealedCellAttackException) {
        }
        catch (OutOfRangeException) {
        }
    }
}

void Board::setShip(Ship &ship, const Coord coord) {
    if (!this->checkCoord(coord)) throw IncorrectShipPositionException();
    if (ship.isHorizontal()) {
        if (!this->checkCoord(Coord{coord.x + ship.getSize(), coord.y}))
            throw IncorrectShipPositionException();
        for (int i = 0; i < ship.getSize(); ++i) {
            if (!this->checkCoordAround(Coord{coord.x + i, coord.y}))
                throw IncorrectShipPositionException();
            if (this->isSegmentAtCoord(Coord{coord.x + i, coord.y}))
                throw IncorrectShipPositionException();
        };
        for (int i = 0; i < ship.getSize(); ++i) {
            this->board_.at(coord.y).at(coord.x + i).segment = ship.getSegment(i);
            this->board_.at(coord.y).at(coord.x + i).value = Cell::CellValue::kShipPart;
        }
    } else {
        if (!this->checkCoord(Coord{coord.x, coord.y + ship.getSize()}))
            throw IncorrectShipPositionException();
        for (int i = 0; i < ship.getSize(); ++i) {
            if (!this->checkCoordAround(Coord{coord.x, coord.y + i}))
                throw IncorrectShipPositionException();
            if (this->isSegmentAtCoord(Coord{coord.x, coord.y + i}))
                throw IncorrectShipPositionException();
        }
        for (int i = 0; i < ship.getSize(); ++i) {
            this->board_.at(coord.y + i).at(coord.x).segment = ship.getSegment(i);
            this->board_.at(coord.y + i).at(coord.x).value = Cell::CellValue::kShipPart;
        }
    }
}

void Board::setShipRandomly(Ship &ship) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dis_x(0, this->getSizeX() - 1);
    std::uniform_int_distribution dis_y(0, this->getSizeY() - 1);
    std::uniform_int_distribution dis_orientation(0, 1);

    while (true) {
        const Coord random_set_coord({dis_x(gen), dis_y(gen)});
        if (const int rand_orientation = dis_orientation(gen);
            rand_orientation == 1)
            ship.setOrientation(Ship::Orientation::kVertical);
        try {
            this->setShip(ship, random_set_coord);
            break;
        } catch (IncorrectShipPositionException) {
        }
    }
}

void Board::revealCells() noexcept {
    for (auto &row: this->board_) for (auto &cell: row) cell.changeStatus();
}

std::vector<std::vector<Board::Cell> > Board::getBoard() const noexcept {
    return this->board_;
}
