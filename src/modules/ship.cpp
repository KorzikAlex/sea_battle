/**
 * @file ship.cpp
 * @author Korzik (alek.korshkov@yandex.ru)
 * @brief Ship file
 * @version 0.1
 * @date 2024-10-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "ship.hpp"

Ship::Ship(int size, Orientation orientation) : size_(size), orientation_(orientation) {
    if (size_ < 1 || size_ > 4) throw std::invalid_argument("Size of ship must be between 1 and 4");
};

Ship::Ship(int size, int orientation) : size_(size), 
orientation_((orientation == static_cast<int>(Orientation::kHorizontal)) ? Orientation::kHorizontal : Orientation::kVertical) {
    if (size_ < 1 || size_ > 4) throw std::invalid_argument("Length of ship must be between 1 and 4");
};

Ship::Ship(int size) : size_(size), orientation_(Orientation::kHorizontal) {
    if (size_ < 1 || size_ > 4) throw std::invalid_argument("Length of ship must be between 1 and 4");
};

void Ship::info() const
{
    std::cout << "Size: " << this->size_ << std::endl;
    std::cout << "Orientation: " << (this->orientation_ == Orientation::kHorizontal ? "Horizontal" : "Vertical") << std::endl;
    std::cout << "Segments: ";
};

int Ship::getSize() const{
    return this->size_;
};

std::vector<Segment> Ship::getSegments() const {
    return this->segments_;
};

bool Ship::isHorizontal() const {
    return this->orientation_ == Orientation::kHorizontal;
};

bool Ship::isVertical() const {
    return this->orientation_ == Orientation::kVertical;
};

void Ship::changeOrientation() {
    if (this->isHorizontal()) {
        this->orientation_ == Orientation::kVertical;
    }
    else {
        this->orientation_ == Orientation::kHorizontal;
    }
};

Ship::~Ship() = default;