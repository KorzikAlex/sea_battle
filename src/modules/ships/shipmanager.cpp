/**
 * @file shipmanager.cpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief Implementation of ShipManager Module
 * @version 0.1
 * @date 2024-10-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "shipmanager.hpp"

ShipManager::ShipManager(std::vector<int> sizes) {
    for (int size: sizes) this->ships_.push_back(Ship(size));
}

Ship &ShipManager::operator[](int index) {
    return this->getShip(index);
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
