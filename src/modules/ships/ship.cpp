/**
 * @file ship.cpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief Implementation of Ship Module
 * @version 0.1
 * @date 2024-10-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>

#include "ships/ship.hpp"

void Ship::Segment::handleDamage() {
    if (this->health == SegmentStatus::kWhole) this->health = SegmentStatus::kDamaged;
    else if (this->health == SegmentStatus::kDamaged) this->health = SegmentStatus::kDestroyed;
}

Ship::Ship(int size, Orientation orientation): size_(size), orientation_(orientation) {
    this->segments_ = std::vector<Segment>(this->size_);
};

Ship::Segment &Ship::operator[](int index) {
    return this->segments_.at(index);
};

bool Ship::isHorizontal() const {
    return this->orientation_ == Orientation::kHorizontal;
};

bool Ship::isVertical() const {
    return this->orientation_ == Orientation::kVertical;
};

bool Ship::isDestroyed() const {
    for (const auto segment: this->segments_) if (segment.health != Segment::SegmentStatus::kDestroyed) return false;
    return true;
};

Ship::Orientation Ship::getOrientation() const {
    return this->orientation_;
};

int Ship::getSize() const {
    return this->size_;
};

Ship::Segment *Ship::getSegment(int index) {
    return &this->segments_.at(index);
};

void Ship::info() {
    std::cout << "Size: " << this->getSize() << std::endl;
    std::cout << "Orientation: " << (this->isHorizontal() ? "Horizontal" : "Vertical") << std::endl;
    std::cout << "Segments: ";
    for (int i = 0; i < this->size_; ++i) {
        switch (this->getSegment(i)->health) {
            case Segment::SegmentStatus::kWhole: {
                std::cout << i << "+";
                break;
            };
            case Segment::SegmentStatus::kDamaged: {
                std::cout << i << "-";
                break;
            };
            case Segment::SegmentStatus::kDestroyed: {
                std::cout << i << "X";
                break;
            };
            default:
                break;
        };
    };
    std::cout << std::endl;
};

void Ship::changeOrientation() {
    if (this->isHorizontal()) this->orientation_ = Orientation::kVertical;
    else if (this->isVertical()) this->orientation_ = Orientation::kHorizontal;
};

void Ship::setOrientation(Orientation orientation) {
    this->orientation_ = orientation;
};

Ship::~Ship() = default;
