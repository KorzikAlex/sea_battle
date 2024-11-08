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
#ifndef SEABATTLE_INCLUDE_ABILITIES_ABILITY_MANAGER_HPP
#define SEABATTLE_INCLUDE_ABILITIES_ABILITY_MANAGER_HPP

#include <queue>

#include "abilities_list.hpp"


class AbilityManager {
public:
    enum class Abilities {
        DoubleAttack,
        Scanner,
        RandomAttack
    };
    AbilityManager(Board& board);
    int getAbilityCount() const;
    bool isEmpty() const;
    void giveRandomAbility();

    std::string returnAbilityName() const;
    Abilities returnAbility() const;

    void useAbility(Coord coord = {-1, -1});
    void popAbility();

    ~AbilityManager();

private:
    std::queue<Abilities> abilities_;
    Board& board_;

    void addAbility(Abilities ability);
};


#endif //SEABATTLE_INCLUDE_ABILITIES_ABILITY_MANAGER_HPP
