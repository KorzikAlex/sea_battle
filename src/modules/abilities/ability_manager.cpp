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


AbilityManager::AbilityManager() {
    std::vector<AbilityCreator *> ability_creators = {
        new DoubleAttackAbilityCreator(),
        new ScannerAbilityCreator(),
        new RandomAttackAbilityCreator()
    };

    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(ability_creators.begin(), ability_creators.end(), gen);
    this->abilities_.push(ability_creators[0]);
}

int AbilityManager::getAbilityCount() const {
    return this->abilities_.size();
}

void AbilityManager::isEmpty() const {
    if (this->abilities_.empty()) throw NoAvailableAbilitiesException("You don't have abilities!");
}

void AbilityManager::addAbility(AbilityCreator* ability_creator) {
    this->abilities_.push(ability_creator);
}

void AbilityManager::popAbility() {
    this->abilities_.pop();
}

void AbilityManager::useAbility(AbilityParameters ap) {
    this->isEmpty();
    AbilityCreator* ability = this->abilities_.front();
    ability->createAbility(ap)->realizeAbility();
    delete ability;
    this->abilities_.pop();
}

void AbilityManager::giveRandomAbility() {
    std::random_device rd;
    std::mt19937 gen(rd());
    switch (gen() % 3) {
        case 0: {
            this->addAbility(new DoubleAttackAbilityCreator);
            break;
        }
        case 1: {
            this->addAbility(new ScannerAbilityCreator);
            break;
        }
        case 2: {
            this->addAbility(new RandomAttackAbilityCreator);
            break;
        }
        default:
            break;
    }
}

AbilityCreator& AbilityManager::returnAbilityCreator(int index) const {
    this->isEmpty();
    std::queue<AbilityCreator*> tmp = this->abilities_;
    for (int i = 0; i < index; ++i) tmp.pop();
    return *tmp.front();
}

AbilityManager::~AbilityManager() {
    while (!this->abilities_.empty())
        this->abilities_.pop();
};

std::string AbilityManager::returnAbilityName() const {
    this->isEmpty();
    return this->abilities_.front()->getName();
}

