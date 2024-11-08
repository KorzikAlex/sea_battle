#include <algorithm>
#include <random>
#include <array>
#include <iostream>

#include "abilities/ability_manager.hpp"

AbilityManager::AbilityManager(Board &board): board_(board) {
    std::array<Abilities, 3> abilities = {Abilities::DoubleAttack, Abilities::Scanner, Abilities::RandomAttack};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(abilities.begin(), abilities.end(), gen);
    abilities_.emplace(abilities[0]);
}

int AbilityManager::getAbilityCount() const {
    return this->abilities_.size();
}

bool AbilityManager::isEmpty() const {
    return this->abilities_.empty();
}

void AbilityManager::addAbility(Abilities ability) {
    this->abilities_.push(ability);
}

void AbilityManager::popAbility() {
    this->abilities_.pop();
}

void AbilityManager::useAbility(Coord coord) {
    Abilities ability = this->abilities_.front();
    // TODO: применить способности корректно
    if (coord.x == -1 && coord.y == -1 && ability == Abilities::RandomAttack)
        RandomAttack(this->board_).realizeAbility();
    else if (ability == Abilities::DoubleAttack)
        DoubleAttack(this->board_, coord).realizeAbility();
    else if (ability == Abilities::Scanner)
        Scanner(this->board_, coord).realizeAbility();
    this->popAbility();
}

void AbilityManager::giveRandomAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());

    switch (gen() % 3) {
        case 0: {
            this->addAbility(Abilities::DoubleAttack);
            break;
        }
        case 1: {
            this->addAbility(Abilities::Scanner);
            break;
        }
        case 2: {
            this->addAbility(Abilities::RandomAttack);
            break;
        }
        default:
            break;
    }
}

std::string AbilityManager::returnAbilityName() const {
    if (this->abilities_.front() == Abilities::Scanner)
        return "Scanner";
    if (this->abilities_.front() == Abilities::DoubleAttack)
        return "DoubleAttack";
    else if (this->abilities_.front() == Abilities::RandomAttack)
        return "RandomAttack";
    return "WTF";
}

AbilityManager::Abilities AbilityManager::returnAbility() const {
    return this->abilities_.front();
}

AbilityManager::~AbilityManager() = default;
