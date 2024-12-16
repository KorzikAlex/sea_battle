#pragma once

#include <queue>
#include <algorithm>
#include <random>
#include <array>

#include "abilities_list.hpp"
#include "ability_creator.hpp"

#include "exceptions/no_available_abilities.hpp"

class AbilityManager {
public:
    AbilityManager();

    int getAbilityCount() const;

    void isEmpty() const;

    void giveRandomAbility();

    std::string returnAbilityName() const;

    AbilityCreator& returnAbilityCreator(int index) const;

    // void useAbility(Coord coord = {-1, -1});

    void useAbility(AbilityParameters ap);

    void popAbility();

    void addAbility(AbilityCreator* ability_creator);

    ~AbilityManager();

private:
    std::queue<AbilityCreator *> abilities_;
};
