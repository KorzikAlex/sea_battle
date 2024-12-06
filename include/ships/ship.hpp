/**
 * @file ship.hpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief Ship module
 * @version 0.1
 * @date 2024-10-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <vector>
#include <iostream>

#include "structures.hpp"

/**
 * @brief Represents a ship in a game.
 *
 * The Ship class encapsulates the properties and behaviors associated with a ship,
 * including its size, orientation, and health status of its segments.
 */
class Ship {
public:
    /**
     * @brief Represents the orientation of a ship.
     *
     * Determines whether the ship is positioned horizontally or vertically.
     */
    enum class Orientation {
        kHorizontal,
        kVertical
    };

    /**
     * @brief Represents a segment of a ship.
     *
     * A ship segment may have one of several statuses indicating its health.
     */
    struct Segment {
        /**
         * @brief Represents the status of a ship segment.
         *
         * Indicates the health of a ship segment which can be whole, damaged, or destroyed.
         */
        enum class SegmentStatus {
            kWhole,
            kDamaged,
            kDestroyed
        };

        /**
         * @brief Represents the health status of a ship segment.
         *
         * Indicates whether the segment is currently whole, damaged, or destroyed.
         */
        SegmentStatus health = SegmentStatus::kWhole;
        /**
         * @brief Handles the damage state of a ship segment.
         *
         * Changes the health status of the segment based on its current state.
         * - If the segment is whole, it transitions to damaged.
         * - If the segment is damaged, it transitions to destroyed.
         */
        void handleDamage(int power = 1);

        Coord segment_coord;
    };

    /**
     * @brief Constructs a Ship object with a given size and orientation.
     *
     * Initializes the Ship object with the specified size and orientation,
     * and sets up its segments.
     *
     * @param size The size of the ship, which determines the number of segments.
     * @param orientation The orientation of the ship (horizontal or vertical).
     */
    explicit Ship(int size, Orientation orientation = Orientation::kHorizontal);

    /**
     * @brief Accesses a ship's segment by index.
     *
     * Provides access to a specific ship segment based on its index.
     *
     * @param index The index of the segment to access.
     * @return A reference to the segment at the specified index.
     */
    Segment &operator[](int index);

    /**
     * @brief Checks if the ship's orientation is horizontal.
     *
     * This method determines whether the ship is oriented horizontally
     * based on its orientation property.
     *
     * @return True if the ship is horizontal, otherwise false.
     */
    bool isHorizontal() const;

    /**
     * @brief Checks if the ship's orientation is vertical.
     *
     * This method determines whether the ship is oriented vertically
     * based on its orientation property.
     *
     * @return True if the ship is vertical, otherwise false.
     */
    bool isVertical() const;

    /**
     * @brief Checks if the ship is destroyed.
     *
     * This method evaluates whether all segments of the ship are in the destroyed state.
     *
     * @return True if all segments are destroyed, otherwise false.
     */
    bool isDestroyed() const;

    /**
     * @brief Retrieves the current orientation of the ship.
     *
     * This method returns the orientation of the ship, which indicates whether
     * the ship is positioned horizontally or vertically.
     *
     * @return The current orientation of the ship.
     */
    Orientation getOrientation() const;

    /**
     * @brief Retrieves the size of the ship.
     *
     * This method returns the size of the ship, which indicates the number of segments it has.
     *
     * @return The size of the ship.
     */
    int getSize() const;

    /**
     * @brief Accesses a specific segment of the ship by index.
     *
     * This method provides access to a particular segment of the ship, allowing
     * manipulation or inspection of its properties.
     *
     * @param index The index of the segment to be accessed.
     * @return A pointer to the segment at the specified index.
     */
    Segment *getSegment(int index);

    /**
     * @brief Displays information about the ship.
     *
     * This method outputs the size, orientation, and health status of each segment of the ship.
     * The orientation is shown as either "Horizontal" or "Vertical" based on the ship's orientation property.
     * Each segment's status is shown using symbols: a '+' indicates a whole segment,
     * a '-' indicates a damaged segment, and an 'X' indicates a destroyed segment.
     */
    void info();

    /**
     * @brief Changes the orientation of the ship.
     *
     * This method toggles the orientation of the ship between horizontal and vertical.
     * If the ship is currently oriented horizontally, it will be changed to vertical and vice versa.
     */
    void changeOrientation();

    /**
     * @brief Sets the orientation of the ship.
     *
     * This method updates the orientation of the ship to the specified value.
     *
     * @param orientation The new orientation to set for the ship (horizontal or vertical).
     */
    void setOrientation(Orientation orientation);

    /**
     * @brief Destructor for the Ship class.
     *
     * This method cleans up resources associated with a Ship object when it is destroyed.
     */
    ~Ship();

private:
    /**
    * @brief Size of the ship.
    *
    * This variable represents the size of the ship, which determines the number of segments
    * that the ship will have.
    */
    int size_;
    /**
     * @brief Describes the orientation of an object.
     *
     * The orientation_ variable indicates the current orientation or direction of an object,
     * which can be used to determine positional alignment or facing direction within the application.
     */
    Orientation orientation_;
    /**
     * @brief Stores the segments that make up a ship.
     *
     * This vector contains the individual segments that represent the structure of a ship.
     * Each segment provides specific details about a part of the ship.
     */
    std::vector<Segment> segments_;
};
