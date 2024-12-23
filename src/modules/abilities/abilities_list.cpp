#include "abilities/abilities_list.hpp"

DoubleAttack::DoubleAttack(Board &board, const Coord coord): board_(board), coord_(coord) {
}

Scanner::Scanner(Board &board, const Coord coord): board_(board), coord_(coord) {
}

RandomAttack::RandomAttack(Board &board): board_(board) {
}

void DoubleAttack::realizeAbility() {
    this->board_.attack(this->coord_, 2);
}

void Scanner::realizeAbility() {
    for (int j = 0; j <= 1; ++j)
        for (int i = 0; i <= 1; ++i) {
            const Coord check_coord({this->coord_.x + i, this->coord_.y + j});
            if (!board_.checkCoord(check_coord)) throw OutOfRangeException();
            if (Board::Cell &board_cell = this->board_.getCell(check_coord); board_cell.isSegmentAt()) {
                std::cout << "Ship in this area." << std::endl;
                return;
            }
        }
    for (int j = 0; j <= 1; ++j)
        for (int i = 0; i <= 1; ++i) {
            const Coord check_coord({this->coord_.x + i, this->coord_.y + j});
            Board::Cell board_cell = this->board_.getCell(check_coord);
            board_cell.changeStatus();
            board_cell.value = Board::Cell::CellValue::kWaterRevealed;
        }
    std::cout << "Sorry. Ship isn't in this area." << std::endl;
}

void RandomAttack::realizeAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution disX(0, this->board_.getSizeX() - 1);
    std::uniform_int_distribution disY(0, this->board_.getSizeY() - 1);
    while (true) {
        const Coord rd_coord = {disX(gen), disY(gen)};
        if (Board::Cell &board_cell = this->board_.getCell(rd_coord); board_cell.isSegmentAt()) {
            if (board_cell.segment->health != Ship::Segment::SegmentHealth::kDestroyed) {
                board_cell.segment->handleDamage();
                if (board_cell.value == Board::Cell::CellValue::kShipPart)
                    board_cell.value = Board::Cell::CellValue::kDamaged;
                else board_cell.value = Board::Cell::CellValue::kDestroyed;
                // std::cout << "The attack was made by position: " << rd_coord.x << " " << rd_coord.y << std::endl;
            } else continue;
            break;
        }
    }
}
