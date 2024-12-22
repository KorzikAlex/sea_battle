#include "ships/ship.hpp"

void Ship::Segment::handleDamage(const int power) noexcept {
    if (this->health == SegmentHealth::kWhole && power == 1) this->health = SegmentHealth::kDamaged;
    else if (this->health == SegmentHealth::kDamaged || (this->health == SegmentHealth::kWhole && power >= 2))
        this->health = SegmentHealth::kDestroyed;
}

Ship::Ship(const int size, const Orientation orientation): size_(size), orientation_(orientation) {
    this->segments_ = std::vector<Segment>(this->size_);
}

Ship::Segment &Ship::operator[](const int index) {
    return this->segments_.at(index);
}

bool Ship::isHorizontal() const noexcept {
    return this->orientation_ == Orientation::kHorizontal;
}

bool Ship::isVertical() const noexcept {
    return this->orientation_ == Orientation::kVertical;
}

bool Ship::isDestroyed() const noexcept {
    for (const auto [health, segment_coord]: this->segments_)
        if (health != Segment::SegmentHealth::kDestroyed) return false;
    return true;
}

Ship::Orientation Ship::getOrientation() const noexcept {
    return this->orientation_;
}

int Ship::getSize() const noexcept {
    return this->size_;
}

Ship::Segment *Ship::getSegment(const int index) {
    return &this->segments_.at(index);
}

void Ship::changeOrientation() noexcept {
    if (this->isHorizontal()) this->orientation_ = Orientation::kVertical;
    else if (this->isVertical()) this->orientation_ = Orientation::kHorizontal;
}

void Ship::setOrientation(const Orientation orientation) noexcept {
    this->orientation_ = orientation;
}

void Ship::setCoord(const Coord coord) noexcept {
    int i = 0;
    for (auto &[health, segment_coord]: this->segments_) {
        if (this->isHorizontal()) segment_coord = {coord.x + i, coord.y};
        else segment_coord = {coord.x, coord.y + i};
        ++i;
    }
}
