#ifndef SEABATTLE_STRUCTURES_HPP
#define SEABATTLE_STRUCTURES_HPP

enum class SegmentStatus {
    kWhole,
    kDamaged,
    kDestroyed
};

enum class CellStatus {
    kHidden,
    kRevealed
};

enum class Orientation {
    kHorizontal,
    kVertical
};

enum class ShipStatus {
    kWhole,
    kDestroyed
};

struct Coord {
    int x;
    int y;
};

struct Segment {
    SegmentStatus health;
    void handleDamage() {
        switch (health) {
            case SegmentStatus::kWhole: {
                health = SegmentStatus::kDamaged;
                break;
            }
            case SegmentStatus::kDamaged: {
                health = SegmentStatus::kDestroyed;
                break;
            }
            default:
                break;
        }
    }
};

struct Cell {
    CellStatus status = CellStatus::kHidden;
    Segment* segment = nullptr;
};

#endif // SEABATTLE_STRUCTURES_HPP
