#include "json_modules/deserialization.hpp"

using json = nlohmann::json;

void Deserialization::from_json(ShipManager &ship_manager, std::string key) {
    const auto &jsm = this->json_file_.at(key);
    std::vector<int> ship_sizes;

    for (const auto &jship: jsm) ship_sizes.push_back(jship.at("length"));

    ship_manager = ShipManager(ship_sizes);

    for (size_t i = 0; i < ship_sizes.size(); i++) {
        std::string key = "ship" + std::to_string(i);
        Ship &ship = ship_manager[i];
        if (jsm.at(key).at("horizontal") == true) ship.setOrientation(Ship::Orientation::kHorizontal);
        else ship.setOrientation(Ship::Orientation::kVertical);

        for (int j = 0; j < ship_sizes[i]; j++) {
            Ship::Segment *segment = ship.getSegment(j);
            segment->health = jsm.at(key).at("segments").at(j).at("health");
        }
    }

    int shipsAlive = ship_sizes.size();
    for (size_t i = 0; i < ship_sizes.size(); i++) {
        Ship &ship = ship_manager[i];
        if (ship.isDestroyed()) shipsAlive--;
    }
    ship_manager.setShipsAlive(shipsAlive);
}

void Deserialization::from_json(Board &board, std::string key) {
    const auto &jf = this->json_file_.at(key);
    board = Board(jf.at("rows"), jf.at("columns"));

    for (int y = 0; y < board.getSizeY(); y++) {
        for (int x = 0; x < board.getSizeX(); x++) {
            std::string key = "cell" + std::to_string(y) + std::to_string(x);
            Board::Cell &cell = board.getCell({x, y});
            cell.coordinate.x = jf.at(key).at("x");
            cell.coordinate.y = jf.at(key).at("y");
            cell.state = jf.at(key).at("state");
            cell.value = jf.at(key).at("value");
        }
    }
}

void Deserialization::from_json(AbilityManager &abilityManager, std::string key) {
    const auto &jam = this->json_file_.at(key);
    abilityManager = AbilityManager();
    abilityManager.popAbility();

    for (const auto &jability: jam.at("abilities")) {
        if (jability == "DoubleAttack") abilityManager.addAbility(AbilityManager::Abilities::DoubleAttack);
        else if (jability == "Scanner") abilityManager.addAbility(AbilityManager::Abilities::Scanner);
        else if (jability == "RandomAttack") abilityManager.addAbility(AbilityManager::Abilities::RandomAttack);
    }
}
