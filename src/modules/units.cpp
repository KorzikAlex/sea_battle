#include "units.hpp"

Unit::Unit(ShipManager &ship_manager, Board &board): ship_manager_(ship_manager), board_(board) {
}

PlayerUnit::PlayerUnit(ShipManager &ship_manager, Board &board, AbilityManager &ability_manager): Unit(ship_manager,
        board), ability_manager_(ability_manager) {
}

PlayerUnit::PlayerUnit(const PlayerUnit &other): Unit(other.ship_manager_, other.board_),
                                                 ability_manager_(other.ability_manager_) {
}

PlayerUnit &PlayerUnit::operator=(const PlayerUnit &other) {
    if (this != &other) {
        this->ship_manager_ = other.ship_manager_;
        this->board_ = other.board_;
    }
    return *this;
}

Board &PlayerUnit::getBoard() const noexcept {
    return this->board_;
}

ShipManager &PlayerUnit::getShipManager() const noexcept {
    return this->ship_manager_;
}

AbilityManager &PlayerUnit::getAbilityManager() const noexcept {
    return this->ability_manager_;
}

BotUnit::BotUnit(ShipManager &ship_manager, Board &board): Unit(ship_manager, board) {
}

BotUnit::BotUnit(const BotUnit &other): Unit(other.ship_manager_, other.board_) {
}

BotUnit &BotUnit::operator=(const BotUnit &other) {
    if (this != &other) {
        this->ship_manager_ = other.ship_manager_;
        this->board_ = other.board_;
    }
    return *this;
}

Board &BotUnit::getBoard() const noexcept {
    return this->board_;
}

ShipManager &BotUnit::getShipManager() const noexcept {
    return this->ship_manager_;
}
