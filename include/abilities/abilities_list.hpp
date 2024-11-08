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

class Ability {
public:
    virtual void realizeAbility() = 0;

    virtual ~Ability() = default;
};

class DoubleAttack : public Ability {
public:
    DoubleAttack(Board &field, Coord coord);

    void realizeAbility() override;

private:
    Board &board_;
    Coord coord_;
};

class Scanner : public Ability {
public:
    Scanner(Board &field, Coord coord);

    void realizeAbility() override;

private:
    Board &board_;
    Coord coord_;
};

class RandomAttack : public Ability {
public:
    RandomAttack(Board &field);

    void realizeAbility() override;

private:
    Board &board_;
};
#endif //SEABATTLE_ABILITIES_INCLUDE_ABILITIES_LIST_HPP
