#pragma once

#include "ships/ship_manager.hpp"
#include "board.hpp"
#include "abilities/ability_manager.hpp"

class Unit {
public:
    Unit(ShipManager &ship_manager, Board &board);

    virtual ShipManager &getShipManager() const noexcept = 0;

    virtual Board &getBoard() const noexcept = 0;

    virtual ~Unit() = default;

protected:
    ShipManager &ship_manager_;
    Board &board_;
};

class PlayerUnit final : public Unit {
public:
    PlayerUnit(ShipManager &ship_manager, Board &board, AbilityManager &ability_manager);

    PlayerUnit(const PlayerUnit &other);

    PlayerUnit &operator=(const PlayerUnit &other);

    ShipManager &getShipManager() const noexcept override;

    Board &getBoard() const noexcept override;

    AbilityManager &getAbilityManager() const noexcept;

private:
    AbilityManager &ability_manager_;
};

class BotUnit final : public Unit {
public:
    BotUnit(ShipManager &ship_manager, Board &board);

    BotUnit(const BotUnit &other);

    BotUnit &operator=(const BotUnit &other);

    ShipManager &getShipManager() const noexcept override;

    Board &getBoard() const noexcept override;
};
