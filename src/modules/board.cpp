#include "board.hpp"

Board::Board(int size_x=10, int size_y=10): size_x_(size_x), size_y_(size_y) {
    for (int i = 0; i < this->size_y_; ++i) {
        std::vector<Cell> cells;
        for (int j = 0; j < this->size_x_; ++j) {
            cells.push_back(Cell{Coord{j, i}, CellStatus::kHidden});
        }
        this->field_.push_back(cells);
    }
};

int Board::getCountRows() const {
    return this->size_y_;
};

int Board::getCountColumns() const {
    return this->size_x_;
};

bool Board::checkCoord(Coord coord) {
    return coord.x < 0 || coord.x >= this->getCountColumns() || coord.y < 0 || coord.y >= this->getCountRows();
};

bool Board::setShip(Ship* ship, Coord coord) {
    if (this->checkCoord(coord)) return false;
    if (ship->isHorizontal()) {
        if ((coord.x + ship->getSize() > this->getCountColumns()) || (coord.y >= this->getCountRows())) return false;
        for (int i = 0; i < ship->getSize(); i++) {
            if (checkCoordinatesAround({coord.x + i, coord.y})) {
                return false;
            }
            if (this->isShipAt({coord.x + i, coord.y})) {
                return false;
            }
        }

        for (int i = 0; i < ship->getSize(); i++) {
            ship->getSegments()[i]->coordinate = Coordinate{coordinate.x, coordinate.y + i};
            field[coord.y*this->columns + coord.x + i].segment = ship->getSegments()[i];
            field[coord.y*this->columns + coord.x + i].value = CellValue::ShipPart;
        }
        return true;
    }
    // Vertically
    if ((coord.y + ship->getSize() > this->getCountRows()) || (coord.x >= this->getCountColumns())) return false;

    for (int i = 0; i < ship->getLength(); i++) {
        if (checkCoordinatesAround({coord.x, coord.y + i})) {
            return false;
        }
        if (this->isShipAt({coord.x, coord.y + i})) {
            return false;
        }
    }

    for (int i = 0; i < ship->getLength(); i++) {
        ship->getSegments()[i]->coordinate = Coordinate{coordinate.x + i, coordinate.y};
        field[(coord.y + i)*this->columns + coord.x].segment = ship->getSegments()[i];
        field[(coord.y + i)*this->columns + coord.x].value = CellValue::ShipPart;
    }
    return true;
};

void init(std::vector<Ship*> ships) {

};