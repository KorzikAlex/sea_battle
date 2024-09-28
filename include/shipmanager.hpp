#ifndef SHIP_MANAGER_HPP
#define SHIP_MANAGER_HPP

#include <ship.hpp>


class ShipManager
{
private:
    std::vector<Ship> ships_;
public:
    explicit ShipManager(std::vector<Ship> ships): ships_(ships) {}; 
};

#endif // SHIP_MANAGER_HPP
