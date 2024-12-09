#include "painter.hpp"

// #include "AbilityCreator.hpp"

void Painter::printException(std::exception &e) const {
    std::cerr << "Exception: " << e.what() << std::endl;
}

void Painter::printAbilityName(std::string ability_name) const {
    std::cout << ability_name << std::endl;
}

void Painter::printShip(Ship ship) const {
    std::cout << "Size: " << ship.getSize() << std::endl;
    if (ship.isHorizontal()) std::cout << "orientation: Horizontal" << std::endl;
    else std::cout << "orientation: Vertical" << std::endl;

    std::cout << "Segments health:" << std::endl;

    for (int i = 0; i < ship.getSize(); ++i) {
        switch (ship.getSegment(i)->health) {
            case Ship::Segment::SegmentStatus::kWhole: {
                std::cout << "Whole" << std::endl;
                break;
            }
            case Ship::Segment::SegmentStatus::kDamaged: {
                std::cout << "Damaged" << std::endl;
                break;
            }
            case Ship::Segment::SegmentStatus::kDestroyed: {
                std::cout << "Destroyed" << std::endl;
                break;
            }
        }
    }
}

void Painter::printCellValue(Board self, Coord coord) const {
    switch (self.getCell(coord).value) {
        case Board::Cell::CellValue::kShipPart:
            std::cout << "\033[1;32m" << "S";
            break;
        case Board::Cell::CellValue::kDamaged:
            std::cout << "\033[1;31m" << "X";
            break;
        case Board::Cell::CellValue::kDestroyed:
            std::cout << "\033[1;30m" << "#";
            break;
        case Board::Cell::CellValue::kWaterHidden:
            std::cout << "\033[1;34m" << "~";
            break;
        case Board::Cell::CellValue::kWaterRevealed:
            std::cout << "\033[1;35m" << "*";
            break;
    }
}

void Painter::printField(Board self) const {
    int size_y = self.getSizeY();
    int size_x = self.getSizeX();
    for (int i = 0; i < size_y; i++) {
        std::cout << "\033[0m" << "  " << i;
        if (i < 10) {
            std::cout << " ";
        }
    }

    std::cout << std::endl;
    for (int i = 0; i < size_y; i++) {
        std::cout << "\033[30m" << "x---";
    }

    std::cout << "\033[30m" << "x" << std::endl;
    for (int y = 0; y < size_x; y++) {
        std::cout << "\033[30m" << "| ";
        for (int x = 0; x < columns; x++) {
            if (self.getField()[y * rows + x].state == CellState::Revealed) {
                this->printCellValue(self, {x, y});
            } else {
                std::cout << "\033[1;34m" << "~";
            }
            std::cout << "\033[30m" << " | ";
        }
        std::cout << "\033[0m" << y;
        std::cout << std::endl;
        for (int i = 0; i < rows; i++) {
            std::cout << "\033[30m" << "x---";
        }
        std::cout << "\033[30m" << "x" << std::endl;
    }
    std::cout << "\033[0m";
}

void Painter::printFields(Field self, Field other) const {
    int rows = self.getRows();
    int columns = self.getColumns();
    std::cout << std::endl;
    for (int i = 0; i < rows; i++) {
        std::cout << "\033[0m" << "  " << i;
        if (i < 10) {
            std::cout << " ";
        }
    }

    std::cout << "    ";
    for (int i = 0; i < rows; i++) {
        std::cout << "\033[0m" << "  " << i;
        if (i < 10) {
            std::cout << " ";
        }
    }

    std::cout << std::endl;
    for (int i = 0; i < rows * 2; i++) {
        if (i == rows) {
            std::cout << "x   ";
        }
        std::cout << "\033[1;30m" << "x---";
    }

    std::cout << "\033[30m" << "x" << std::endl;
    for (int y = 0; y < rows; y++) {
        std::cout << "\033[30m" << "| ";
        int index = 0;
        for (int x = 0; x < columns * 2; x++) {
            if (x < columns) {
                if (self.getField()[y * rows + x].state == CellState::Revealed) {
                    this->printCellValue(self, {x, y});
                } else {
                    std::cout << "\033[1;34m" << "~";
                }
            }

            if (x == columns) {
                std::cout << "\033[0m" << y;
                std::cout << "\033[30m" << " | ";
            }

            if (x >= columns) {
                if (other.getField()[(y - 1) * other.getRows() + index].state == CellState::Revealed) {
                    this->printCellValue(other, {index, y - 1});
                } else {
                    std::cout << "\033[1;34m" << "~";
                }
            }
            index++;
            std::cout << "\033[30m" << " | ";
        }

        std::cout << std::endl;
        for (int i = 0; i < rows * 2; i++) {
            if (i == rows) {
                std::cout << "x   ";
            }
            std::cout << "\033[30m" << "x---";
        }
        std::cout << "\033[30m" << "x" << std::endl;
    }
    std::cout << "\033[0m" << std::endl;
}
