#include "units.hpp"

Unit::Unit(ShipManager &ship_manager, Board &board): ship_manager_(ship_manager), board_(board) {
};

Unit::~Unit() = default;

PlayerUnit::PlayerUnit(ShipManager &ship_manager, Board &board, AbilityManager &ability_manager): Unit(ship_manager,
        board), ability_manager_(ability_manager) {
};

PlayerUnit::PlayerUnit(const PlayerUnit &other): Unit(other.ship_manager_, other.board_),
                                                 ability_manager_(other.ability_manager_) {
};

PlayerUnit &PlayerUnit::operator=(const PlayerUnit &other) {
    if (this != &other) {
        this->ship_manager_ = other.ship_manager_;
        this->board_ = other.board_;
    }
    return *this;
};

Board &PlayerUnit::getBoard() {
    return this->board_;
}

ShipManager &PlayerUnit::getShipManager() {
    return this->ship_manager_;
}

AbilityManager &PlayerUnit::getAbilityManager() {
    return this->ability_manager_;
}

BotUnit::BotUnit(ShipManager &shipManager, Board &board): Unit(shipManager, board) {
};

BotUnit::BotUnit(const BotUnit &other): Unit(other.ship_manager_, other.board_) {
};

BotUnit &BotUnit::operator=(const BotUnit &other) {
    if (this != &other) {
        this->ship_manager_ = other.ship_manager_;
        this->board_ = other.board_;
    }
    return *this;
}

Board &BotUnit::getBoard() {
    return this->board_;
};

ShipManager &BotUnit::getShipManager() {
    return this->ship_manager_;
};
