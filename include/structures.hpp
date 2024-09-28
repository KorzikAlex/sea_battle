#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

enum class SegmentStatus
{
    Whole,
    Damaged,
    Destroyed
};
enum class ShipStatus
{
    Whole,
    Damaged,
    Destroyed
};
enum class CeilStatus
{
    hidden,
    visible
};
enum class Orientation
{
    Horizontal,
    Vertical
};

struct Coord
{
    int x_, y_;
};

#endif // STRUCTURES_HPP