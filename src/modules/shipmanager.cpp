#include "shipmanager.hpp"

ShipManager::ShipManager(std::vector<int> sizes): n_(sizes.size()) {
    for (int size:sizes) this->ships_.push_back(new Ship(size));
}

ShipManager::ShipManager(int n, std::vector<int> sizes): n_(n) {
    for (int i = 0; i < this->n_; ++i) this->ships_.push_back(new Ship(sizes[i]));
};

ShipManager::ShipManager(int n, int sizes[]): n_(n) {
    for (int i = 0; i < this->n_; ++i) this->ships_.push_back(new Ship(sizes[i]));
};

ShipManager::ShipManager(int n, int* sizes): n_(n) {
    for (int i = 0; i < this->n_; ++i) this->ships_.push_back(new Ship(sizes[i]));
}

std::vector<Ship*> ShipManager::getShips() const {
    return this->ships_;
}

int ShipManager::getShipCount() const {
    return this->n_;
}

void ShipManager::addShip(int size) {
    this->ships_.push_back(new Ship(size));
    n_++;
}

ShipManager::~ShipManager() = default;