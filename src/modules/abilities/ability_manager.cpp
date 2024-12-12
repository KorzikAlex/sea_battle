/**
 * @file ability_manager.cpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2024-11-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "abilities/ability_manager.hpp"


AbilityManager::AbilityManager(Board &board): board_(board) {
    std::array<Abilities, 3> abilities = {Abilities::kDoubleAttack, Abilities::kScanner, Abilities::kRandomAttack};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(abilities.begin(), abilities.end(), gen);
    this->abilities_.push(abilities[0]);
}

int AbilityManager::getAbilityCount() const {
    return this->abilities_.size();
}

void AbilityManager::isEmpty() const {
    if (this->abilities_.empty()) throw NoAvailableAbilitiesException("You don't have abilities!");
}

void AbilityManager::addAbility(Abilities ability) {
    this->abilities_.push(ability);
}

void AbilityManager::popAbility() {
    this->abilities_.pop();
}

void AbilityManager::useAbility(Coord coord) {
    Abilities ability = this->abilities_.front();
    if (coord.x == -1 && coord.y == -1 && ability == Abilities::kRandomAttack)
        RandomAttack(this->board_).realizeAbility();
    else if (ability == Abilities::kDoubleAttack)
        DoubleAttack(this->board_, coord).realizeAbility();
    else if (ability == Abilities::kScanner)
        Scanner(this->board_, coord).realizeAbility();
    this->popAbility();
}
void AbilityManager::useAbility(AbilityParameters ap) {
    this->isEmpty();
    Abilities ability = this->abilities_.front();
    useAbility();
    ability->createAbility(ap)->implementAbility();
    this->popAbility();
}

void AbilityManager::giveRandomAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());

    switch (gen() % 3) {
        case 0: {
            this->addAbility(Abilities::kDoubleAttack);
            break;
        }
        case 1: {
            this->addAbility(Abilities::kScanner);
            break;
        }
        case 2: {
            this->addAbility(Abilities::kRandomAttack);
            break;
        }
        default:
            break;
    }
}

std::string AbilityManager::returnAbilityName() const {
    if (this->abilities_.front() == Abilities::kScanner)
        return "Scanner";
    if (this->abilities_.front() == Abilities::kDoubleAttack)
        return "DoubleAttack";
    if (this->abilities_.front() == Abilities::kRandomAttack)
        return "RandomAttack";
    throw "Can't return Ability Name";
}

AbilityManager::Abilities AbilityManager::returnAbility() const {
    return this->abilities_.front();
}

AbilityManager::~AbilityManager() = default;
