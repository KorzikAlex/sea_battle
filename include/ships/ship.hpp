#pragma once

#include <vector>

#include "structures.hpp"

class Ship {
public:
    enum class Orientation {
        kHorizontal,
        kVertical
    };

    struct Segment {
        enum class SegmentHealth {
            kWhole,
            kDamaged,
            kDestroyed
        };

        SegmentHealth health = SegmentHealth::kWhole;
        Coord coord;

        void handleDamage(int power = 1) noexcept;
    };

    explicit Ship(int size, Orientation orientation = Orientation::kHorizontal);

    Segment &operator[](int index);

    bool isHorizontal() const noexcept;

    bool isVertical() const noexcept;

    bool isDestroyed() const noexcept;

    Orientation getOrientation() const noexcept;

    int getSize() const noexcept;

    Segment *getSegment(int index);

    void changeOrientation() noexcept;

    void setOrientation(Orientation orientation) noexcept;

    void setCoord(Coord coord) noexcept;

    ~Ship() = default;

private:
    int size_;
    Orientation orientation_;
    std::vector<Segment> segments_;
};
