/**
 * @file structures.hpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief Structures for modules
 * @version 0.1
 * @date 2024-10-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
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

/**
 * @brief Struct of coordinates
 * 
 */
struct Coord {
    int x;
    int y;
};

/**
 * @brief Struct for Ship Segment
 * 
 */
struct Segment {
    SegmentStatus health = SegmentStatus::kWhole;
};

/**
 * @brief Struct for Cell of Board
 * 
 */
struct Cell {
    CellStatus status = CellStatus::kHidden;
    Segment *segment = nullptr;
};

#endif // SEABATTLE_STRUCTURES_HPP
