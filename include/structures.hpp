#ifndef SEABATTLE_STRUCTURES_HPP
#define SEABATTLE_STRUCTURES_HPP

enum class SegmentStatus
{
    kWhole,
    kDamaged,
    kDestroyed
};

enum class CellStatus
{
    kHidden,
    kEmpty
};

enum class Orientation
{
    kHorizontal,
    kVertical
};

struct Coord
{
    int x;
    int y;
};

struct Segment {
    Coord pos;
    SegmentStatus health;
};

struct Cell {
    Coord pos;
    CellStatus state;
    Segment* segment = nullptr;
};

#endif // STRUCTURES_HPP