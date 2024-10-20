#ifndef SEABATTLE_SHIP_MANAGER_HPP
#define SEABATTLE_SHIP_MANAGER_HPP

#include <vector>

#include "structures.hpp"
#include "ship.hpp"

class ShipManager {
    public:
        /**
         * @brief Construct a new Ship Manager object
         * 
         * @param sizes 
         */
        explicit ShipManager(std::vector<int> sizes);
        /**
         * @brief Copy constructor of ShipManager
         * 
         * @param other 
         */
        ShipManager(const ShipManager& other);
        /**
         * @brief Move constructor of ShipManager
         * 
         * @param other 
         */
        ShipManager(ShipManager&& other) noexcept;
        /**
         * @brief Overloading [] operator to get Ship reference
         * 
         * @param i 
         * @return Ship& 
         */
        Ship& operator[](int i);
        /**
         * @brief Copy assignment of ShipManager
         * 
         * @param other 
         * @return ShipManager& 
         */
        ShipManager& operator=(const ShipManager& other);
        /**
         * @brief Move assignment of ShipManager
         * 
         * @param other 
         * @return ShipManager& 
         */
        ShipManager& operator=(ShipManager&& other) noexcept;
        /**
         * @brief Get the reference of Ship object
         * 
         * @param index 
         * @return Ship& 
         */
        Ship& getShip(int index);
        /**
         * @brief Get the Ship count in Ship Manager
         * 
         * @return int 
         */
        int getShipCount() const;
        /**
         * @brief Create and add new Ship object to Ship Manager
         * 
         * @param size 
         */
        void addShip(int size);
        /**
         * @brief Add Ship object to Ship Manager
         * 
         * @param ship 
         */
        void addShip(Ship ship);
        /**
         * @brief Delete Ship object to Ship Manager
         * 
         * @param index 
         */
        void eraseShip(int index);
        /**
         * @brief Destructor of Ship Manager object
         * 
         */
        ~ShipManager();
    private:
        std::vector<Ship> ships_;
};

#endif // SEABATTLE_SHIP_MANAGER_HPP
