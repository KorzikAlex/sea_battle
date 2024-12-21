#include "ships/ship_manager.hpp"

ShipManager::ShipManager(std::vector<int> sizes): ships_(sizes.begin(), sizes.end()) {
}

Ship &ShipManager::operator[](const int index) {
    return this->getShip(index);
}

int ShipManager::getShipCount() const noexcept {
    return this->ships_.size();
}

Ship &ShipManager::getShip(const int index) {
    return this->ships_.at(index);
}

Ship &ShipManager::getShip(const Ship::Segment *segment) {
    for (int i = 0; i < this->ships_.size(); ++i)
        for (int j = 0; j < this->ships_.at(i).getSize(); ++j)
            if (this->ships_.at(i).getSegment(j) == segment) return this->ships_.at(i);
    throw OutOfRangeException();
}

Ship &ShipManager::getShip(const Coord coord) {
    for (Ship &ship: this->ships_)
        for (int i = 0; i < ship.getSize(); i++)
            if (ship.getSegment(i)->segment_coord.x == coord.x && ship.getSegment(i)->segment_coord.y == coord.y)
                return ship;
    throw OutOfRangeException();
}

void ShipManager::addShip(const int size, const Ship::Orientation orientation) {
    this->ships_.push_back(Ship(size, orientation));
}

void ShipManager::eraseShip(const int index) {
    this->ships_.erase(this->ships_.begin() + index);
}

void ShipManager::eraseAllShips() noexcept {
    this->ships_.clear();
}

void ShipManager::changeShipOrientation(const int index, const Ship::Orientation new_orientation) {
    this->ships_.at(index).setOrientation(new_orientation);
}

void ShipManager::checkShips() {
    this->n_alive_ships_ = 0;
    for (const Ship &ship: this->ships_) if (!ship.isDestroyed()) n_alive_ships_++;
}

int ShipManager::getShipsAlive() {
    this->checkShips();
    return this->n_alive_ships_;
}
