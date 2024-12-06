#pragma once

#include "ships/ship_manager.hpp"
#include "board.hpp"
#include "abilities/ability_manager.hpp"

class Unit {
public:
    Unit(ShipManager &ship_manager, Board &board);

    virtual ShipManager &getShipManager() = 0;

    virtual Board &getBoard() = 0;

    virtual ~Unit();

protected:
    ShipManager &ship_manager_;
    Board &board_;
};

class PlayerUnit : public Unit {
public:
    PlayerUnit(ShipManager &shipManager, Board &field, AbilityManager &ability_manager);

    PlayerUnit(const PlayerUnit &other);

    PlayerUnit &operator=(const PlayerUnit &other);

    ShipManager &getShipManager() override;

    Board &getBoard() override;

    AbilityManager &getAbilityManager();

private:
    AbilityManager &ability_manager_;
};

class BotUnit : public Unit {
public:
    BotUnit(ShipManager &shipManager, Board &board);

    BotUnit(const BotUnit &other);

    BotUnit &operator=(const BotUnit &other);

    ShipManager &getShipManager() override;

    Board &getBoard() override;
};
