#include "json_modules/serizalization.hpp"

Serialization::Serialization(nlohmann::json &json_file): json_file_(json_file) {
}

void Serialization::to_json(ShipManager &ship_manager, const std::string &key) {
    nlohmann::json jsm;
    for (int i = 0; i < ship_manager.getShipCount(); ++i) {
        Ship &temp = ship_manager[i];
        const std::string temp_key = "ship" + std::to_string(i);
        jsm[temp_key] = {
            {"size", temp.getSize()},
            {"orientation", temp.getOrientation()},
            {"segments", nlohmann::json::array()}
        };
        for (int j = 0; j < temp.getSize(); ++j) {
            Ship::Segment *tempSegment = temp.getSegment(j);
            jsm[temp_key]["segments"].push_back({
                {"health", tempSegment->health},
                {"x", tempSegment->coord.x},
                {"y", tempSegment->coord.y}
            });
        }
    }

    this->json_file_[key] = jsm;
}

void Serialization::to_json(Board &board, const std::string &key) const {
    nlohmann::json jb;

    jb["size_x"] = board.getSizeX();
    jb["size_y"] = board.getSizeY();

    for (int y = 0; y < board.getSizeY(); ++y)
        for (int x = 0; x < board.getSizeX(); ++x) {
            const std::string temp_key = "cell" + std::to_string(y) + std::to_string(x);
            jb[temp_key] = {
                {"status", board.getCell({x, y}).status},
                {"value", board.getCell({x, y}).value}
            };
        }

    this->json_file_[key] = jb;
}

void Serialization::to_json(const AbilityManager &ability_manager, const std::string &key) {
    nlohmann::json jam;

    for (int i = 0; i < ability_manager.getAbilityCount(); ++i)
        jam["abilities"].push_back(ability_manager.returnAbilityCreator(0).getName());
    if (ability_manager.getAbilityCount() == 0) jam["abilities"].push_back("");
    this->json_file_[key] = jam;
}



