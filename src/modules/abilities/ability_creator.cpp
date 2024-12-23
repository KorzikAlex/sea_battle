#include "abilities/ability_creator.hpp"

DoubleAttackAbilityCreator::DoubleAttackAbilityCreator() {}

std::string DoubleAttackAbilityCreator::getName() const noexcept {
    return "DoubleAttack";
}

bool DoubleAttackAbilityCreator::isUsingCoordinate() const noexcept {
    return true;
}

Ability *DoubleAttackAbilityCreator::createAbility(AbilityParameters &ap) {
    return new DoubleAttack(ap.board, ap.coord);
}

ScannerAbilityCreator::ScannerAbilityCreator() {
}

std::string ScannerAbilityCreator::getName() const noexcept {
    return "Scanner";
}

bool ScannerAbilityCreator::isUsingCoordinate() const noexcept {
    return true;
}

Ability *ScannerAbilityCreator::createAbility(AbilityParameters &ap) {
    return new Scanner(ap.board, ap.coord);
}

RandomAttackAbilityCreator::RandomAttackAbilityCreator() {
}

std::string RandomAttackAbilityCreator::getName() const noexcept {
    return "RandomAttack";
}

bool RandomAttackAbilityCreator::isUsingCoordinate() const noexcept {
    return false;
}

Ability *RandomAttackAbilityCreator::createAbility(AbilityParameters &ap) {
    return new RandomAttack(ap.board);
}
