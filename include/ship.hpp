/**
 * @file ship.hpp
 * @author KorzikAlex (you@domain.com)
 * @brief hpp file of ship class
 * @version 0.1
 * @date 2024-10-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef SEABATTLE_SHIP_HPP
#define SEABATTLE_SHIP_HPP

#include <vector>
#include <iostream>

#include "structures.hpp"


class Ship {
    public:
        /**
         * @brief Constructor of new Ship object
         *
         * @param size
         * @param orientation
         */
        explicit Ship(int size, Orientation orientation);
        /**
         * @brief Constructor of new Ship object
         *
         * @param size
         */
        explicit Ship(int size);
        /**
         * @brief Copy constructor of Ship object
         *
         * @param other
         */
        Ship(const Ship &other);
        /**
         * @brief Move constructor of Ship object
         *
         * @param other
         */
        Ship(Ship&& other) noexcept;
        /**
         * @brief Copy assignment of Ship object
         *
         * @param other
         * @return Ship&
         */
        Ship& operator=(const Ship& other);
        /**
         * @brief Move assignment of Ship object
         *
         * @param other
         * @return Ship&
         */
        Ship& operator=(Ship&& other) noexcept;
        /**
        * @brief operator [] to get reference of SHip's segment
        *
        * @param index
        * @return Segment&
        */
        Segment& operator[](int index);
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
        Segment* getSegment(int index);
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

#endif // SEABATTLE_SHIP_HPP