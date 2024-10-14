#ifndef SEABATTLE_SHIP_H
#define SEABATTLE_SHIP_H

#include <iostream>
#include <vector>

#include "structures.hpp"

class Ship {
    public:
        explicit Ship(int size, Orientation orientation);
        explicit Ship(int size, int orientation);
        explicit Ship(int size);

        ~Ship();

        bool isHorizontal() const;
        bool isVertical() const;
        int getSize() const;
        std::vector<Segment> getSegments() const;
        void info() const;
        
        void changeOrientation();

    private:
        int size_;
        Orientation orientation_;
        std::vector<Segment> segments_;
};

#endif // SHIP_H