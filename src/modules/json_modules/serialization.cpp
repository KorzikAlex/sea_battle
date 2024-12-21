#include "json_modules/serizalization.hpp"

Serialization::Serialization(nlohmann::json& json_file): json_file_(json_file) {
}

void Serialization::to_json(ShipManager &ship_manager, std::string key) {
    nlohmann::json jsm{};

    for (int i = 0; i < ship_manager.getShipCount(); i++) {
        Ship &temp = ship_manager[i];
        key = "ship" + std::to_string(i);
        jsm[key] = {
            {"size", temp.getSize()},
            {"horizontal", temp.isHorizontal()},
            {"segments", nlohmann::json::array()}
        };
        for (int j = 0; j < temp.getSize(); j++) {
            Ship::Segment *tempSegment = temp.getSegment(j);
            jsm[key]["segments"].push_back({"health", tempSegment->health});
        }
    }

    this->json_file_[key] = jsm;
}

void Serialization::to_json(Board &board, std::string key) const {
    nlohmann::json jb{};

    jb["size_y"] = board.getSizeY();
    jb["size_x"] = board.getSizeX();

    for (int y = 0; y < board.getSizeY(); y++) {
        for (int x = 0; x < board.getSizeX(); x++) {
            key = "cell" + std::to_string(y) + std::to_string(x);
            jb[key] = {
                {"status", board.getCell({x, y}).status},
                {"value", board.getCell({x, y}).value}
            };
        }
    }

    this->json_file_[key] = jb;
}

void Serialization::to_json(const AbilityManager &ability_manager, const std::string &key) {
    nlohmann::json jam{};

    for (int i = 0; i < ability_manager.getAbilityCount(); i++)
        jam["abilities"].push_back(ability_manager.returnAbilityCreator(0).getName());
    if (ability_manager.getAbilityCount() == 0) jam["abilities"].push_back("");
    this->json_file_[key] = jam;
}


Serialization::~Serialization() = default;
