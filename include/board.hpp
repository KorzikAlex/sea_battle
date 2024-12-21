#pragma once

#include <vector>
#include <random>

#include "ships/ship.hpp"
#include "structures.hpp"

#include "exceptions/out_of_range.hpp"
#include "exceptions/incorrect_ship_position.hpp"
#include "exceptions/revealed_cell_attack.hpp"

class Board {
public:
    struct Cell {
        enum class CellVisibilityStatus {
            kHidden,
            kRevealed
        };

        enum class CellValue : char {
            kShipPart = 'S',
            kDamaged = 'D',
            kDestroyed = 'X',
            kWaterHidden = '~',
            kWaterRevealed = '*'
        };

        CellVisibilityStatus status;
        Ship::Segment *segment;
        CellValue value;

        void changeStatus() noexcept;

        bool isSegmentAt() const noexcept;
    };

    explicit Board(int size_x, int size_y);

    Board(const Board &other) noexcept;

    Board(Board &&other) noexcept;

    Board &operator=(const Board &other) noexcept;

    Board &operator=(Board &&other) noexcept;

    int getSizeX() const noexcept;

    int getSizeY() const noexcept;

    bool checkCoord(Coord coord) const noexcept;

    Cell &getCell(Coord coord);

    bool checkCoordAround(Coord coord) noexcept;

    bool isSegmentAtCoord(Coord coord) noexcept;

    void setShip(Ship &ship, Coord coord);

    void setShipRandomly(Ship &ship);

    void attack(Coord coord, int power = 1);

    Coord attackRandomly();

    void revealCoordinatesAround(Ship &ship);

    void revealCells() noexcept;

    std::vector<std::vector<Cell> > getBoard() const noexcept;

    ~Board() = default;

private:
    int size_x_;
    int size_y_;
    std::vector<std::vector<Cell> > board_;
};
