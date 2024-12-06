#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "ships/ship_manager.hpp"
#include "board.hpp"
#include "abilities/ability_manager.hpp"

class Deserialization {
public:
    Deserialization(nlohmann::json& json_file) : json_file_(json_file) {};

    void from_json(ShipManager& ship_manager, std::string key);
    void from_json(Board& board, std::string key);
    void from_json(AbilityManager& ability_manager, std::string key);
private:
    nlohmann::json& json_file_;
};