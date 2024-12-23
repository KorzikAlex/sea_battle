# pragma once

#include "abilities/ability_creator.hpp"
#include "abilities/abilities_list.hpp"

class AbilityCreator {
public:
    virtual Ability *createAbility(AbilityParameters &ap) = 0;

    virtual std::string getName() const noexcept = 0;

    virtual bool isUsingCoordinate() const noexcept = 0;

    virtual ~AbilityCreator() {}
};

class DoubleAttackAbilityCreator : public AbilityCreator {
public:
    DoubleAttackAbilityCreator();

    Ability *createAbility(AbilityParameters &ap) override;

    std::string getName() const noexcept override;

    bool isUsingCoordinate() const noexcept override;
};

class ScannerAbilityCreator : public AbilityCreator {
public:
    ScannerAbilityCreator();

    Ability *createAbility(AbilityParameters &ap) override;

    std::string getName() const noexcept override;

    bool isUsingCoordinate() const noexcept override;
};

class RandomAttackAbilityCreator : public AbilityCreator {
public:
    RandomAttackAbilityCreator();

    Ability *createAbility(AbilityParameters &ap) override;

    std::string getName() const noexcept override;

    bool isUsingCoordinate() const noexcept override;
};
