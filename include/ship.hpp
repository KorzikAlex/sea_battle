#ifndef SHIP_H
#define SHIP_H

#include "structures.hpp"

#include <vector>

class Ship{
public:
    explicit Ship(int size, Orientation orientation) : size_(size), orientation_(orientation) {};
    explicit Ship(int size, int orientation) : size_(size), orientation_(orientation ? Orientation::Horizontal : Orientation::Vertical) {};
    ~Ship() = default;
private:
    int size_;
    Orientation orientation_ = Orientation::Horizontal;
    std::vector<SegmentStatus> segments_;
};

#endif // SHIP_H