#include "shipmanager.hpp"

ShipManager::ShipManager(std::vector<int> sizes) {
    for (int size:sizes) this->ships_.push_back(Ship(size));
};

ShipManager::ShipManager(const ShipManager& other): ships_(other.ships_) {};

ShipManager::ShipManager(ShipManager&& other) noexcept: ships_(std::move(other.ships_)){};

ShipManager& ShipManager::operator=(const ShipManager& other) {
    if (this != &other) this->ships_ = other.ships_;
    return *this;
};

ShipManager &ShipManager::operator=(ShipManager &&other) noexcept {
    if (this != &other) ships_ = std::move(other.ships_);
    return *this;
};

int ShipManager::getShipCount() const {
    return this->ships_.size();
};

Ship& ShipManager::getShip(int index) {
    return this->ships_[index];
};

void ShipManager::addShip(int size) {
    this->ships_.push_back(Ship(size));
};

void ShipManager::addShip(Ship ship) {
    this->ships_.push_back(ship);
};

void ShipManager::eraseShip(int index) {
    this->ships_.erase(this->ships_.begin() + index);
};

ShipManager::~ShipManager() = default;