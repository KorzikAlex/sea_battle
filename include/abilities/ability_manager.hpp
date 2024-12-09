/**
 * @file ability_manager.hpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2024-11-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <queue>
#include <algorithm>
#include <random>
#include <array>

#include "abilities_list.hpp"

#include "exceptions/no_available_abilities.hpp"


/**
 * @class AbilityManager
 *
 * @brief Manages the abilities within the game, including maintaining a queue of abilities and providing mechanisms
 *        to use, add, and randomly assign abilities.
 */
class AbilityManager {
public:
    /**
    * @enum Abilities
    *
    * @brief Enum class representing the different types of abilities available in the game.
    */
    enum class Abilities {
        kDoubleAttack,
        kScanner,
        kRandomAttack
    };

    /**
     * @brief Constructs an AbilityManager object that manages game abilities.
     *
     * This constructor initializes the AbilityManager with a given game board,
     * randomizes a predefined set of abilities, and sets the first ability in
     * the randomized list as the active ability.
     *
     * @param board A reference to the game board that the abilities will interact with.
     * @return An instance of the AbilityManager class.
     */
    AbilityManager(Board &board);

    /**
     * @brief Retrieves the count of abilities currently managed by the AbilityManager.
     *
     * This method returns the number of abilities contained within the internal queue.
     *
     * @return The number of abilities in the manager.
     */
    int getAbilityCount() const;

    /**
     * @brief Checks if the AbilityManager's ability queue is empty.
     *
     * This method determines whether there are any abilities currently managed
     * by the AbilityManager by checking if the internal ability queue is empty.
     *
     */
    void isEmpty() const;

    /**
     * @brief Assigns a random ability to the ability queue.
     *
     * This method randomly selects one of the predefined abilities and adds it
     * to the internal ability queue. The abilities that can be randomly assigned
     * include DoubleAttack, Scanner, and RandomAttack.
     */
    void giveRandomAbility();

    /**
     * @brief Retrieves the name of the front ability in the queue.
     *
     * This method returns a string representing the name of the front ability
     * in the internal queue of abilities. Possible return values include
     * "Scanner", "DoubleAttack", "RandomAttack", or "WTF" if the ability is unknown.
     *
     * @return The name of the front ability in the queue.
     */
    std::string returnAbilityName() const;

    /**
     * @brief Retrieves the front ability from the ability queue.
     *
     * This method returns the front ability in the internal queue of abilities.
     * The returned ability represents the next ability that can be used.
     *
     * @return The front ability in the queue.
     */
    Abilities returnAbility() const;

    /**
     * @brief Uses an ability at the specified coordinates.
     *
     * This method applies the front ability from the ability queue at the given coordinates.
     * It handles the usage of different types of abilities, including RandomAttack, DoubleAttack,
     * and Scanner, by checking the coordinates and the type of the front ability.
     *
     * @param coord The coordinates at which the ability should be applied. Special values for
     *              coord (e.g., (-1, -1)) may be used to trigger specific behavior for certain abilities.
     */
    void useAbility(Coord coord = {-1, -1});

    /**
     * @brief Removes the front ability from the ability queue.
     *
     * This method pops the front ability from the internal queue,
     * effectively removing the ability that was previously at the front.
     */
    void popAbility();

    /**
     * @brief Adds a new ability to the abilities queue.
     *
     * @param ability The ability to be added to the queue.
     */
    void addAbility(Abilities ability);
    /**
     * @brief Destructs the AbilityManager object.
     *
     * This destructor is responsible for cleaning up resources used by the AbilityManager.
     * Its implementation is defaulted, indicating that no special actions are required upon
     * destruction of an AbilityManager instance.
     */
    ~AbilityManager();

private:
    /**
    * @brief A queue storing the available abilities.
    *
    * This member variable maintains the current list of abilities
    * available for use by the AbilityManager. Abilities are managed
    * in a FIFO (First In, First Out) order, where the ability at the
    * front of the queue is the next one to be used.
    */
    std::queue<Abilities> abilities_;
    /**
     * @brief A reference to the game board associated with the AbilityManager.
     *
     * This member variable allows the AbilityManager to interact with and
     * manipulate the game board, enabling abilities to have effects within the game.
     */
    Board &board_;


};
