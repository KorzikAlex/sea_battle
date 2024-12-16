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

    AbilityParameters(Board &board, ShipManager &sm, Coord &coord): board(board), ship_manager(sm), coord(coord) {
    }
};

class Ability {
public:
    virtual void realizeAbility() = 0;

    virtual ~Ability();
};

class DoubleAttack : public Ability {
public:
    DoubleAttack(Board &board, Coord coord);

    void realizeAbility() override;

private:
    Board &board_;
    Coord coord_;
};

class Scanner : public Ability {
public:
    Scanner(Board &board, Coord coord);

    void realizeAbility() override;

private:
    Board &board_;
    Coord coord_;
};

class RandomAttack : public Ability {
public:
    RandomAttack(Board &board);

    void realizeAbility() override;

private:
    Board &board_;
};
