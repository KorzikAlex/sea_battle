#pragma once

#include <vector>

#include "ship.hpp"

#include "exceptions/out_of_range.hpp"

class ShipManager {
public:
    explicit ShipManager() : ships_({}) {};
    explicit ShipManager(std::vector<int> sizes);

    Ship &operator[](int index);

    Ship &getShip(int index);

    Ship &getShip(const Ship::Segment *segment);

    Ship &getShip(Coord coord);

    int getShipCount() const noexcept;

    void addShip(int size, Ship::Orientation orientation = Ship::Orientation::kHorizontal);

    void eraseShip(int index);

    void eraseAllShips() noexcept;

    void changeShipOrientation(int index, Ship::Orientation new_orientation);

    int getShipsAlive();

    ~ShipManager() = default;

private:
    std::vector<Ship> ships_;
    int n_alive_ships_ = 0;

    void checkShips();
};
