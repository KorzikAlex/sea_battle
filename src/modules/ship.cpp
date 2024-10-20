#include "ship.hpp"

Ship::Ship(int size, Orientation orientation): size_(size), orientation_(orientation) {
    if (this->size_ < 1 || this->size_ > 4) throw std::invalid_argument("Size of ship must be between 1 and 4");
    this->segments_ = std::vector<Segment>(this->size_);
};

Ship::Ship(int size): size_(size), orientation_(Orientation::kHorizontal) {
    if (this->size_ < 1 || this->size_ > 4) throw std::invalid_argument("Length of ship must be between 1 and 4");
    this->segments_ = std::vector<Segment>(this->size_);
};

Ship::Ship(const Ship &other): size_(other.size_), orientation_(other.orientation_), segments_(other.segments_) {};

Ship::Ship(Ship&& other) noexcept: size_(other.size_), orientation_(other.orientation_), segments_(std::move(other.segments_)) {
    other.size_ = 0;
    other.orientation_ = Orientation::kHorizontal;
};

Ship& Ship::operator=(const Ship& other) {
    if (this != &other) {
        this->size_ = other.size_;
        this->orientation_ = other.orientation_;
        this->segments_ = other.segments_;
    }
    return *this;
};

Ship& Ship::operator=(Ship&& other) noexcept {
    if (this != &other) {
        size_ = other.size_;
        orientation_ = other.orientation_;
        segments_ = std::move(other.segments_);

        other.size_ = 0;
        other.orientation_ = Orientation::kHorizontal;
    }
    return *this;
};

Segment& Ship::operator[](int index) {
    return this->segments_[index];
};

bool Ship::isHorizontal() const {
    return this->orientation_ == Orientation::kHorizontal;
};

bool Ship::isVertical() const {
    return this->orientation_ == Orientation::kVertical;
};

Orientation Ship::getOrientation() const {
    return this->orientation_;
};

int Ship::getSize() const {
    return this->size_;
};

Segment* Ship::getSegment(int index) {
    return &this->segments_[index];
};

void Ship::info() {
    std::cout << "Size: " << this->getSize() << std::endl;
    std::cout << "Orientation: " << (this->isHorizontal() ? "Horizontal" : "Vertical") << std::endl;
    std::cout << "Segments: ";
    for (int i = 0; i < this->size_; i++) {
        switch (this->getSegment(i)->health) {
            case SegmentStatus::kWhole:
                std::cout << i << "+";
                break;
            case SegmentStatus::kDamaged:
                std::cout << i << "-";
                break;
            case SegmentStatus::kDestroyed:
                std::cout << i <<"X";
                break;
            default:
                break;
        }
    }
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
