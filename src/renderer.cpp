#include "renderer.hpp"

void Renderer::printBoard(Board board) const {
    const int size_x = board.getSizeX();
    const int size_y = board.getSizeY();

    for (int i = 0; i < size_y; i++) {
        std::cout << "\033[0m" << "  " << i;
        if (i < 10) std::cout << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < size_y; i++)
        std::cout << "\033[30m" << "x---";

    std::cout << "\033[30m" << "x" << std::endl;
    for (int y = 0; y < size_y; y++) {
        std::cout << "\033[30m" << "| ";
        for (int x = 0; x < size_x; x++) {
            if (board.getCell({x, y}).status == Board::Cell::CellVisibilityStatus::kRevealed)
                this->printCellValue(board, {x, y});
            else std::cout << "\033[1;34m" << "~";
            std::cout << "\033[30m" << " | ";
        }
        std::cout << "\033[0m" << y;
        std::cout << std::endl;
        for (int i = 0; i < size_y; i++) std::cout << "\033[30m" << "x---";
        std::cout << "\033[30m" << "x" << std::endl;
    }
    std::cout << "\033[0m";
}

void Renderer::printBoards(Board self_board, Board other_board) const {
    const int size_x = self_board.getSizeX();
    const int size_y = self_board.getSizeY();
    std::cout << std::endl;
    for (int i = 0; i < size_y; ++i) {
        std::cout << "\033[0m" << "  " << i;
        std::cout << " ";
    }
    std::cout << "    ";
    for (int i = 0; i < size_y; ++i) {
        std::cout << "\033[0m" << "  " << i;
        std::cout << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < size_y * 2; ++i) {
        if (i == size_y) std::cout << "x   ";
        std::cout << "\033[1;30m" << "x---";
    }
    std::cout << "\033[30m" << "x" << std::endl;
    for (int y = 0; y < size_y; ++y) {
        std::cout << "\033[30m" << "| ";
        for (int x = 0; x < size_x; ++x) {
            if (self_board.getCell({x, y}).status == Board::Cell::CellVisibilityStatus::kRevealed)
                this->printCellValue(self_board, {x, y});
            else std::cout << "\033[1;34m" << "~";
            std::cout << "\033[30m" << " | ";
        }

        std::cout << "\033[0m" << y;
        std::cout << "\033[30m" << " | ";

        for (int x = 0; x < size_x; ++x) {
            if (other_board.getCell({x, y}).status == Board::Cell::CellVisibilityStatus::kRevealed)
                this->printCellValue(other_board, {x, y});
            else std::cout << "\033[1;34m" << "~";
            std::cout << "\033[30m" << " | ";
        }
        std::cout << std::endl;
        for (int i = 0; i < size_y * 2; ++i) {
            if (i == size_y) std::cout << "x   ";
            std::cout << "\033[30m" << "x---";
        }
        std::cout << "\033[30m" << "x" << std::endl;
    }
    std::cout << "\033[0m" << std::endl;
}

void Renderer::printException(const std::exception &e) const noexcept{
    std::cerr << "\033[1;31m" << "Exception: " << e.what() << "\033[0m" << std::endl;
}

void Renderer::printAbilityName(const std::string &ability_name) const noexcept {
    std::cout << ability_name << std::endl;
}

void Renderer::printCellValue(Board board, Coord coord) const {
    switch (board.getCell(coord).value) {
        case Board::Cell::CellValue::kShipPart: {
            std::cout << "\033[1;32m" << "S";
            break;
        }
        case Board::Cell::CellValue::kDamaged: {
            std::cout << "\033[1;31m" << "D";
            break;
        }
        case Board::Cell::CellValue::kDestroyed: {
            std::cout << "\033[1;38m" << "X";
            break;
        }
        case Board::Cell::CellValue::kWaterHidden: {
            std::cout << "\033[1;34m" << "~";
            break;
        }
        case Board::Cell::CellValue::kWaterRevealed: {
            std::cout << "\033[1;35m" << "*";
            break;
        }
    }
}