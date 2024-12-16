# pragma once

#include "abilities/ability_creator.hpp"
#include "abilities/abilities_list.hpp"

class AbilityCreator {
public:
    virtual Ability *createAbility(AbilityParameters &ap) = 0;

    virtual std::string getName() const = 0;

    virtual bool isUsingCoordinate() = 0;

    virtual ~AbilityCreator();
};

class DoubleAttackAbilityCreator : public AbilityCreator {
public:
    DoubleAttackAbilityCreator();

    std::string getName() const override;

    bool isUsingCoordinate() override;

    Ability *createAbility(AbilityParameters &ap) override;
};

class ScannerAbilityCreator : public AbilityCreator {
public:
    ScannerAbilityCreator();

    std::string getName() const override;

    bool isUsingCoordinate() override;

    Ability *createAbility(AbilityParameters &ap) override;
};

class RandomAttackAbilityCreator : public AbilityCreator {
public:
    RandomAttackAbilityCreator();

    std::string getName() const override;

    bool isUsingCoordinate() override;

    Ability *createAbility(AbilityParameters &ap) override;
};
