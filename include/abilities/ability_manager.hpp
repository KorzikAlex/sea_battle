#pragma once

#include <queue>
#include <random>
#include <algorithm>

#include "abilities_list.hpp"
#include "ability_creator.hpp"

#include "exceptions/no_available_abilities.hpp"

class AbilityManager {
public:
    AbilityManager();

    int getAbilityCount() const noexcept;

    void isEmpty() const;

    void giveRandomAbility();

    AbilityCreator& returnAbilityCreator(int index) const;

    void useAbility(AbilityParameters ap);

    void popAbility() noexcept;

    void addAbility(AbilityCreator* ability_creator);

    ~AbilityManager();

private:
    std::queue<AbilityCreator *> abilities_;
};
