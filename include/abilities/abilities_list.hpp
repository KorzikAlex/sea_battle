/**
 * @file abilities_list.hpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2024-11-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef SEABATTLE_INCLUDE_ABILITIES_ABILITIES_LIST_HPP
#define SEABATTLE_INCLUDE_ABILITIES_ABILITIES_LIST_HPP

#include "structures.hpp"
#include "board.hpp"

/**
 * @class Ability
 * @brief Abstract base class representing a generic ability.
 *
 * The Ability class serves as an interface for different types of abilities
 * that can be realized. Derived classes must implement the realizeAbility
 * method to define the specific behavior of the ability.
 *
 * @fn virtual void Ability::realizeAbility() = 0
 * @brief Pure virtual function to be overridden by derived classes.
 * This function defines the specific behavior of the ability.
 *
 * @fn virtual Ability::~Ability()
 * @brief Virtual destructor for the Ability class.
 * Allows derived classes to clean up resources during destruction.
 */
class Ability {
public:
    /**
     * @fn virtual void Ability::realizeAbility() = 0
     * @brief Pure virtual function to be implemented by derived classes.
     * This function specifies how the ability is realized in derived classes.
     */
    virtual void realizeAbility() = 0;

    /**
     * @brief Virtual destructor for the Ability class.
     *
     * Ensures that derived class destructors are called when an Ability object is destroyed.
     */
    virtual ~Ability() = default;
};

/**
 * @class DoubleAttack
 * @brief Represents an ability that allows for a double attack on the game board.
 *
 * The DoubleAttack class is a specific type of ability that targets a coordinate
 * on the board and performs an attack twice on the specified location.
 * This class extends the abstract Ability class and implements the realizeAbility method.
 *
 * @fn DoubleAttack::DoubleAttack(Board &field, Coord coord)
 * @brief Constructor for the DoubleAttack class.
 * @param field Reference to the game board where the double attack will be performed.
 * @param coord Coordinate on the board where the double attack is targeted.
 *
 * @fn void DoubleAttack::realizeAbility() override
 * @brief Implements the realization of the double attack ability.
 * This function defines how the double attack is applied to the specified coordinate.
 */
class DoubleAttack : public Ability {
public:
    /**
    * @class DoubleAttack
     * @brief Concrete class representing a double attack ability.
     *
     * The DoubleAttack class defines the specific behavior for performing
     * a double attack on a given board and at a specified coordinate.
     *
     * @fn DoubleAttack::DoubleAttack(Board &field, Coord coord)
     * @brief Constructs a DoubleAttack ability.
     *
     * @param field Reference to the game board where the attack will take place.
     * @param coord The coordinate on the board where the attack will be executed.
     */
    DoubleAttack(Board &field, Coord coord);

    /**
     * @brief Executes the double attack ability on the specified coordinate.
     *
     * The realizeAbility function performs two consecutive attack actions on the board
     * at the given coordinate. This function overrides the pure virtual function
     * defined in the Ability base class.
     */
    void realizeAbility() override;

private:
    /**
    * @var DoubleAttack::board_
    * @brief Reference to the game board where the ability will be applied.
    *
    * This variable holds a reference to the game board. It is used by the DoubleAttack
    * class to perform actions and modifications directly on the game board.
    */
    Board &board_;
    /**
     * @var DoubleAttack::coord_
     * @brief Stores the coordinate where the DoubleAttack will be executed.
     *
     * This variable holds the coordinate on the game board at which the DoubleAttack
     * ability will be performed. It is used to specify the target location for
     * the double attack action.
     */
    Coord coord_;
};

/**
 * @class Scanner
 * @brief A class representing a scanning ability in the game.
 *
 * The Scanner class inherits from the Ability class and is used to perform a specific
 * scanning action on a game board at a given coordinate.
 *
 * @fn Scanner::Scanner(Board &field, Coord coord)
 * @brief Constructs a Scanner object with a reference to the game board and a specific coordinate.
 * @param field Reference to the game board on which the ability will be realized.
 * @param coord Coordinate on the game board where the ability will be applied.
 *
 * @fn void Scanner::realizeAbility() override
 * @brief Overrides the base class method to implement the scanner's specific behavior.
 * This function defines how the scanning ability will be performed on the game board.
 */
class Scanner : public Ability {
public:
    /**
    * @class Scanner
    * @brief Represents a scanning ability in a specified coordinate on a board.
    *
    * The Scanner class is a specific implementation of an Ability.
    * It is designed to scan a given coordinate on a provided board.
    *
    * @fn Scanner::Scanner(Board &field, Coord coord)
    * @brief Constructs a Scanner object with a reference to a board and a coordinate.
    *
    * @param field Reference to the board on which the Scanner operates.
    * @param coord The coordinate on the board to be scanned.
    */
    Scanner(Board &field, Coord coord);

    /**
     * @brief Executes the scanning ability on the specified coordinate.
     *
     * This function scans a 2x2 area on the board starting from the given coordinate.
     * It checks for any segments of ships within this area. If a segment is found,
     * it prints the position of the ship segment and exits. If no segments are found,
     * it updates the status of each cell within the scanned area and prints a message
     * indicating that no ship was found.
     *
     * @throws std::invalid_argument if the coordinates to be checked are out of bounds.
     */
    void realizeAbility() override;

private:
    /**
    * @var Scanner::board_
    * @brief Reference to the board on which the Scanner operates.
    *
    * This member variable holds a reference to the Board object. It is used by the
    * Scanner class to perform scan operations on the specified board in the context
    * provided by the Scanner's coordinate.
    */
    Board &board_;
    /**
     * @var Scanner::coord_
     * @brief The coordinate on the board that the Scanner operates on.
     *
     * This member variable holds the x and y coordinates on the board where
     * the Scanner performs its scanning operations. It defines the starting
     * point for the scan on the provided board.
     */
    Coord coord_;
};

/**
 * @class RandomAttack
 * @brief Represents a random attack ability within a game board.
 *
 * This class provides an implementation of a random attack ability that targets
 * different locations on the game board.
 *
 * @fn RandomAttack::RandomAttack(Board &field)
 * @brief Constructs a new RandomAttack object.
 *
 * This constructor initializes a RandomAttack instance with a reference to a game board,
 * setting up the context in which the random attacks will occur.
 *
 * @param field Reference to the game board where the random attacks will be performed.
 */
class RandomAttack : public Ability {
public:
    /**
    * @class RandomAttack
    * @brief Represents a random attack ability within a game board.
    *
    * This class provides an implementation of a random attack ability that targets
    * different locations on the game board.
    *
    * @fn RandomAttack::RandomAttack(Board &field)
    * @brief Constructs a new RandomAttack object.
    *
    * This constructor initializes a RandomAttack instance with a reference to a game board,
    * setting up the context in which the random attacks will occur.
    *
    * @param field Reference to the game board where the random attacks will be performed.
    */
    RandomAttack(Board &field);

    /**
     * @fn void RandomAttack::realizeAbility()
     * @brief Executes a random attack on the game board.
     *
     * This function randomly selects a coordinate on the game board and inflicts
     * damage on a segment at that location, if present. The attack continues
     * to randomly select coordinates until a segment is found and damaged.
     *
     * This method overrides the pure virtual function defined in the Ability base class.
     */
    void realizeAbility() override;

private:
    /**
    * @var Board& board_
    * @brief Reference to a game board used by the RandomAttack ability.
    *
    * The board_ member variable holds a reference to the game board on which the
    * RandomAttack ability operates. It ensures that the ability can interact with
    * and modify the state of the board during its execution.
    */
    Board &board_;
};
#endif //SEABATTLE_ABILITIES_INCLUDE_ABILITIES_LIST_HPP
