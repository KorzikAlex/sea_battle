#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

#include "ships/ship_manager.hpp"
#include "board.hpp"
#include "abilities/ability_manager.hpp"

class Serialization {
public:
    explicit Serialization(nlohmann::json &json_file);

    ~Serialization();

    void to_json(ShipManager &ship_manager, std::string key);

    void to_json(Board &board, std::string key);

    void to_json(AbilityManager &ability_manager, std::string key);

private:
    nlohmann::json &json_file_;
};
