/**
 * @file ship_manager.cpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief Implementation of ShipManager Module
 * @version 0.1
 * @date 2024-10-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "ships/ship_manager.hpp"

ShipManager::ShipManager(std::vector<int> sizes): ships_(sizes.begin(), sizes.end()) {
};

Ship &ShipManager::operator[](int index) {
    return this->getShip(index); // get reference of ship by index
};

int ShipManager::getShipCount() const {
    return this->ships_.size(); // get count of ships
};

Ship &ShipManager::getShip(int index) {
    if (index >= this->ships_.size() || index < 0) throw std::out_of_range("Ship index out of range");
    return this->ships_.at(index);
};

Ship &ShipManager::getShip(Ship::Segment *segment) {
    for (int i = 0; i < this->ships_.size(); ++i)
        for (int j = 0; j < this->ships_.at(i).getSize(); ++j)
            if (this->ships_.at(i).getSegment(j) == segment) return this->ships_.at(i);
    throw OutOfRangeException("Ship does not exist");
}

Ship &ShipManager::getShip(Coord coord) {
    for (Ship &ship: this->ships_)
        for (int i = 0; i < ship.getSize(); i++)
            if (ship.getSegment(i)->segment_coord.x == coord.x && ship.getSegment(i)->segment_coord.y == coord.y)
                return ship;
    throw OutOfRangeException("Ship does not exist");
}

void ShipManager::addShip(int size, Ship::Orientation orientation) {
    this->ships_.push_back(Ship(size, orientation));
};

void ShipManager::eraseShip(int index) {
    if (index < 0 || index >= this->ships_.size()) throw std::out_of_range("Ship index out of range");
    this->ships_.erase(this->ships_.begin() + index);
};

void ShipManager::eraseAllShips() {
    this->ships_.clear();
}

void ShipManager::changeShipOrientation(int index, Ship::Orientation new_orientation) {
    if (index >= this->ships_.size() || index < 0) throw std::out_of_range("Ship index out of range");
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

ShipManager::~ShipManager() = default;
