#pragma once

#include <iostream>
#include <sstream>

#include "units.hpp"
#include "json_modules/file_wrapper.hpp"

class GameState {
public:
    GameState(PlayerUnit &player, BotUnit &bot);

    std::string getHash(const std::string& data);

    void loadGame(const std::string &file_name);

    void saveGame(const std::string &file_name);

    void placeShips(ShipManager& shipManager, Board& board);

    PlayerUnit &getPlayer();

    BotUnit &getBot();

    ~GameState();

private:
    PlayerUnit &player_;
    BotUnit &bot_;
};
