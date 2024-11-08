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
#ifndef SEABATTLE_INCLUDE_SHIPS_SHIP_HPP
#define SEABATTLE_INCLUDE_SHIPS_SHIP_HPP

#include <vector>

class Ship {
public:
    /**
     * @brief Orientation of Ship enum class
     * 
     */
    enum class Orientation {
        kHorizontal,
        kVertical
    };

    struct Segment {
        /**
         * @brief Status of health segment
         * 
         */
        enum class SegmentStatus {
            kWhole,
            kDamaged,
            kDestroyed
        };
        SegmentStatus health = SegmentStatus::kWhole;
        /**
         * @brief function to deal damage on segment
         * 
         */
        void handleDamage();
    };

    /**
     * @brief Constructor of new Ship object
     *
     * @param size
     * @param orientation
     */
    explicit Ship(int size, Orientation orientation = Orientation::kHorizontal);

    /**
    * @brief Overloading operator [] to get reference of SHip's segment
    *
    * @param index
    * @return Segment&
    */
    Segment &operator[](int index);

    /**
    * @brief Check if ship is horizontal
    *
    * @return true
    * @return false
    */
    bool isHorizontal() const;

    /**
     * @brief Check if ship is horizontal
     *
     * @return true
     * @return false
     */
    bool isVertical() const;

    /**
     * @brief Check if all segments are destroyed
     *
     * @return true
     * @return false
     */
    bool isDestroyed() const;

    /**
     * @brief Get the Orientation object
     *
     * @return Orientation
     */
    Orientation getOrientation() const;

    /**
     * @brief Get the size of Ship object
     *
     * @return int
     */
    int getSize() const;

    /**
     * @brief Get the Segment object of Ship
     *
     * @param index
     * @return Segment&
     */
    Segment *getSegment(int index);

    /**
     * @brief Get info of ship object
     *
     */
    void info();

    /**
     * @brief change orientation of ship
     *
     */
    void changeOrientation();

    /**
     * @brief Set the Orientation for ship object
     *
     * @param orientation
     */
    void setOrientation(Orientation orientation);

    /**
     * @brief Destructor the Ship object
     *
     */
    ~Ship();

private:
    int size_;
    Orientation orientation_;
    std::vector<Segment> segments_;
};

#endif // SEABATTLE_INCLUDE_SHIPS_SHIP_HPP
