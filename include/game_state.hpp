#pragma once

#include "units.hpp"

class GameState {
public:
    GameState(PlayerUnit &player, BotUnit &bot);

    void loadGame(const std::string &file_name);

    void saveGame(const std::string &file_name);

    PlayerUnit &getPlayer();

    BotUnit &getBot();

    ~GameState();

private:
    PlayerUnit &player_;
    BotUnit &bot_;
};
