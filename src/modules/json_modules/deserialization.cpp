#include "json_modules/deserialization.hpp"
Deserialization::Deserialization(nlohmann::json& json_file) : json_file_(json_file) {};

void Deserialization::from_json(ShipManager &ship_manager, const std::string &key) {
    const auto &jsm = this->json_file_[key];
    std::vector<int> ship_sizes;

    for (const auto &jship: jsm) ship_sizes.push_back(jship["size"]);

    ship_manager = ShipManager(ship_sizes);

    for (size_t i = 0; i < ship_sizes.size(); i++) {
        std::string temp_key = "ship" + std::to_string(i);
        Ship &ship = ship_manager[i];
        if (jsm[temp_key]["horizontal"] == true) ship.setOrientation(Ship::Orientation::kHorizontal);
        else ship.setOrientation(Ship::Orientation::kVertical);

        for (int j = 0; j < ship_sizes[i]; j++) {
            Ship::Segment *segment = ship.getSegment(j);
            segment->health = jsm[temp_key]["segments"][j]["health"];
        }
    }
}

void Deserialization::from_json(Board &board, std::string key) {
    const auto &jf = this->json_file_.at(key);
    board = Board(jf["size_x"], jf["size_y"]);

    for (int y = 0; y < board.getSizeY(); y++) {
        for (int x = 0; x < board.getSizeX(); x++) {
            key = "cell" + std::to_string(y) + std::to_string(x);
            Board::Cell &cell = board.getCell({x, y});
            cell.status = jf.at(key).at("status");
            cell.value = jf.at(key).at("value");
        }
    }
}

void Deserialization::from_json(AbilityManager &abilityManager, std::string key) {
    const auto &jam = this->json_file_.at(key);
    // abilityManager = AbilityManager();
    abilityManager.popAbility();

    for (const auto &jability: jam.at("abilities")) {
        if (jability == "DoubleAttack") abilityManager.addAbility(new DoubleAttackAbilityCreator());
        else if (jability == "Scanner") abilityManager.addAbility(new ScannerAbilityCreator());
        else if (jability == "RandomAttack") abilityManager.addAbility(new RandomAttackAbilityCreator());
    }
}
