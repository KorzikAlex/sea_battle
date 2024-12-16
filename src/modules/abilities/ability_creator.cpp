#include "abilities/ability_creator.hpp"

DoubleAttackAbilityCreator::DoubleAttackAbilityCreator() {}

std::string DoubleAttackAbilityCreator::getName() const {
    return "DoubleAttack";
}

bool DoubleAttackAbilityCreator::isUsingCoordinate() {
    return true;
}

Ability * DoubleAttackAbilityCreator::createAbility(AbilityParameters &ap) {
    return new DoubleAttack(ap.board, ap.coord);
}

ScannerAbilityCreator::ScannerAbilityCreator() {
}

std::string ScannerAbilityCreator::getName() const {
    return "Scanner";
}

bool ScannerAbilityCreator::isUsingCoordinate() {
    return true;
}

Ability * ScannerAbilityCreator::createAbility(AbilityParameters &ap) {
    return new Scanner(ap.board, ap.coord);
}

RandomAttackAbilityCreator::RandomAttackAbilityCreator() {
}

std::string RandomAttackAbilityCreator::getName() const {
    return "RandomAttack";
}

bool RandomAttackAbilityCreator::isUsingCoordinate() {
    return false;
}

AbilityCreator::~AbilityCreator() = default;

Ability * RandomAttackAbilityCreator::createAbility(AbilityParameters &ap) {
    return new RandomAttack(ap.board);
}


