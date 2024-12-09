#pragma once

#include <iostream>
#include <sstream>
#include <fstream>

#include "units.hpp"
#include "json_modules/file_wrapper.hpp"

// TODO: добавить описания
class GameState {
public:
    GameState(PlayerUnit &player, BotUnit &bot);

    std::string getHash(const std::string& data);

    void loadGame(const std::string &file_name);

    void saveGame(const std::string &file_name);

    void placeShips(ShipManager& shipManager, Board& board);

    PlayerUnit &getPlayer();

    BotUnit &getBot();
    
    bool& getIsAbilityUsed();

    void setIsAbilityUsed(bool value);

    int& getCurrentDamage();

    void setCurrentDamage(int damage);

    ~GameState();

private:
    PlayerUnit &player_;
    BotUnit &bot_;
    bool is_ability_used_cond_ = false;
    int current_damage_ = 0;
};
