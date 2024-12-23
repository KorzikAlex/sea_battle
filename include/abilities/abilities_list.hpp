#pragma once

#include <iostream>
#include <random>

#include "structures.hpp"
#include "board.hpp"
#include "ships/ship_manager.hpp"

#include "exceptions/out_of_range.hpp"

struct AbilityParameters {
    Board &board;
    ShipManager &ship_manager;
    Coord &coord;

    AbilityParameters(Board &board, ShipManager &ship_manager, Coord &coord): board(board),
                                                                              ship_manager(ship_manager),
                                                                              coord(coord) {
    }
};

class Ability {
public:
    virtual void realizeAbility() = 0;

    virtual ~Ability() = default;
};

class DoubleAttack : public Ability {
public:
    explicit DoubleAttack(Board &board, Coord coord);

    void realizeAbility() override;

private:
    Board &board_;
    Coord coord_;
};

class Scanner : public Ability {
public:
    explicit Scanner(Board &board, Coord coord);

    void realizeAbility() override;

private:
    Board &board_;
    Coord coord_;
};

class RandomAttack : public Ability {
public:
    explicit RandomAttack(Board &board);

    void realizeAbility() override;

private:
    Board &board_;
};
