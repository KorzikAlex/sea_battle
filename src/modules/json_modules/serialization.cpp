#include "json_modules/serizalization.hpp"

void Serialization::to_json(ShipManager& ship_manager, std::string key) {
    nlohmann::json jsm = nlohmann::json{};

    for (int i = 0; i < ship_manager.getShipCount(); i++) {
        Ship& temp = ship_manager[i];
        key = "ship" + std::to_string(i);
        jsm[key] = {
            {"length", temp.getSize()},
            {"horizontal", temp.isHorizontal()},
            {"segments", nlohmann::json::array()}
        };

        for (int j = 0; j < temp.getSize(); j++) {
            Segment* tempSegment = temp.getSegment(j);
            jsm[key]["segments"].push_back({
                {"x", tempSegment->coordinate.x},
                {"y", tempSegment->coordinate.y},
                {"health", tempSegment->health}
            });
        }
    }

    j[key] = jsm;
}

void Serialization::to_json(Board& board, std::string key) {
    nlohmann::json jf = nlohmann::json{};

    jf["rows"] = board.getSizeY();
    jf["columns"] = board.getSizeX();

    std::vector<Cell> temp = board.getField();
    for (int y = 0; y < board.getSizeY(); y++) {
        for (int x = 0; x < board.getSizeX(); x++) {
            key = "cell" + std::to_string(y) + std::to_string(x);
            jf[key] = {
                {"x", temp[y*board.getSizeY() + x].coordinate.x},
                {"y", temp[y*board.getSizeY() + x].coordinate.y},
                {"state", temp[y*board.getSizeY() + x].state},
                {"value", temp[y*board.getSizeY() + x].value}
            };
        }
    }

    j[key] = jf;
}

void  Serialization::to_json(AbilityManager& ability_manager, std::string key) {
    nlohmann::json jam = nlohmann::json{};

    for (int i = 0; i < ability_manager.getAbilityCount(); i++) {
        jam["abilities"].push_back(
            ability_manager.getCreator(i).getName()
        );
    }
    if (ability_manager.getAbilityCount() == 0) {
        jam["abilities"].push_back("");
    }
    j[key] = jam;
}