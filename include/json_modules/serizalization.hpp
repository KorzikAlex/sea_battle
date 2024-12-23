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

    void to_json(ShipManager &ship_manager, const std::string &key);

    void to_json(Board &board, const std::string &key) const;

    void to_json(const AbilityManager &ability_manager, const std::string &key);

    ~Serialization();

private:
    nlohmann::json &json_file_;
};
