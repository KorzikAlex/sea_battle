/**
  * @file ship_manager.hpp
  * @author KorzikAlex (alek.korshkov@yandex.ru)
  * @brief ShipManager module
  * @version 0.1
  * @date 2024-10-20
  *
  * @copyright Copyright (c) 2024
  *
  */
#pragma once

#include <vector>
#include <stdexcept>
#include <string>

#include "ship.hpp"

#include "exceptions/out_of_range.hpp"

/**
 * @brief Manages a collection of Ship objects
 */
class ShipManager {
public:
    ShipManager() : ships_({}) {};
    /**
     * @brief Constructs a ShipManager with a given list of ship sizes
     *
     * @param sizes a vector of integers representing the sizes of the ships to be managed
     */
    explicit ShipManager(std::vector<int> sizes);

    /**
     * @brief Accesses a ship at the specified index.
     *
     * This operator provides access to the Ship object at the given index within
     * the ShipManager.
     *
     * @param index The index of the ship to access.
     * @return A reference to the Ship object at the specified index.
     */
    Ship &operator[](int index);

    /**
     * @brief Retrieves a ship by its index.
     *
     * This method returns a reference to the Ship object stored at the specified index
     * within the ShipManager's collection.
     *
     * @param index The index of the ship to retrieve.
     * @return A reference to the Ship at the specified index.
     */
    Ship &getShip(int index);

    // TODO: добавить описание
    Ship &getShip(Ship::Segment *segment);

    Ship &getShip(Coord coord);

    /**
     * @brief Retrieves the number of ships managed by the ShipManager.
     *
     * This method returns the count of Ship objects currently stored in the ShipManager.
     *
     * @return The number of Ship objects managed by the ShipManager.
     */
    int getShipCount() const;

    /**
     * @brief Adds a Ship to the ShipManager
     *
     * This method adds a Ship object with the specified size to the
     * ShipManager's collection of ships.
     *
     * @param size The size of the Ship to be added.
     */
    void addShip(int size, Ship::Orientation orientation = Ship::Orientation::kHorizontal);

    /**
     * @brief Erases the Ship at the specified index from the collection.
     *
     * This method removes a Ship object located at the provided index
     * within the ShipManager's collection.
     *
     * @param index The index of the Ship to be erased.
     */
    void eraseShip(int index);

    // TODO: добавить описание eraseAllShips
    void eraseAllShips();

    // TODO: добавить описание changeShipOrientation
    void changeShipOrientation(int index, Ship::Orientation new_orientation);

    // TODO: добавить описание checkShips
    void checkShips();
    int getShipsAlive() const;
    /**
     * @brief Destructor for the ShipManager class
     *
     * This destructor cleans up resources allocated by the ShipManager class
     * and ensures that all managed Ship objects are correctly deallocated.
     */
    ~ShipManager();

private:
    /**
     * @brief A vector storing Ship objects managed by ShipManager.
     */
    std::vector<Ship> ships_;
    int n_alive_ships_ = 0;
};
