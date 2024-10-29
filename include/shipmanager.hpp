 /**
  * @file shipmanager.hpp
  * @author KorzikAlex (alek.korshkov@yandex.ru)
  * @brief ShipManager module
  * @version 0.1
  * @date 2024-10-20
  *
  * @copyright Copyright (c) 2024
  *
  */
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
      * @brief Overloading [] operator to get Ship reference
      *
      * @param index
      * @return Ship&
      */
     Ship &operator[](int index);
     /**
      * @brief Get the reference of Ship object
      *
      * @param index
      * @return Ship&
      */
     Ship &getShip(int index);

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
