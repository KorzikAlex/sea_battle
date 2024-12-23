#pragma once

#include <iostream>
#include <sstream>
#include <fstream>

#include "units.hpp"
#include "json_modules/file_wrapper.hpp"
#include "json_modules/deserialization.hpp"
#include "json_modules/serizalization.hpp"

#include "exceptions/hash_mismatch.hpp"

class GameState {
public:
    GameState(PlayerUnit &player, BotUnit &bot);

    std::string getHash(const std::string& data) const noexcept;

    void loadGame(const std::string &file_name);

    void saveGame(const std::string &file_name) const;

    void placeShips(ShipManager& shipManager, Board& board);

    PlayerUnit &getPlayer() const noexcept;

    BotUnit &getBot() const noexcept;

    ~GameState() = default;

private:
    PlayerUnit &player_;
    BotUnit &bot_;
};
