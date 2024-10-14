#ifndef SEABATTLE_SHIP_MANAGER_HPP
#define SEABATTLE_SHIP_MANAGER_HPP

#include <vector>

#include "structures.hpp"
#include "ship.hpp"

class ShipManager
{
    public:
        explicit ShipManager(std::vector<int> sizes);
        explicit ShipManager(int n, std::vector<int> sizes);
        explicit ShipManager(int n, int sizes[]);
        explicit ShipManager(int n, int* sizes);

        ~ShipManager();

        std::vector<Ship*> ShipManager::getShips() const;
        int ShipManager::getShipCount() const;
        void ShipManager::addShip(int length);

    private:
        std::vector<Ship*> ships_;
        int n_;
};

#endif // SHIP_MANAGER_HPP
