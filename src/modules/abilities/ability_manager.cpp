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

int AbilityManager::getAbilityCount() const noexcept {
    return this->abilities_.size();
}

void AbilityManager::isEmpty() const {
    if (this->abilities_.empty()) throw NoAvailableAbilitiesException();
}

void AbilityManager::addAbility(AbilityCreator* ability_creator) {
    this->abilities_.push(ability_creator);
}

void AbilityManager::popAbility() noexcept {
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
    switch (std::mt19937 gen(rd()); gen() % 3) {
        case 0: {
            this->addAbility(new DoubleAttackAbilityCreator());
            break;
        }
        case 1: {
            this->addAbility(new ScannerAbilityCreator());
            break;
        }
        case 2: {
            this->addAbility(new RandomAttackAbilityCreator());
            break;
        }
        default:
            break;
    }
}

AbilityCreator& AbilityManager::returnAbilityCreator(const int index) const {
    this->isEmpty();
    std::queue<AbilityCreator*> tmp = this->abilities_;
    for (int i = 0; i < index; ++i) tmp.pop();
    return *tmp.front();
}

AbilityManager::~AbilityManager() {
    while (!this->abilities_.empty()) {
        delete this->abilities_.front();
        this->abilities_.pop();
    }
}
