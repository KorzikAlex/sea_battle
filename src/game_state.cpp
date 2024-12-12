#include "game_state.hpp"

GameState::GameState(PlayerUnit &player, BotUnit &bot): player_(player), bot_(bot),
                                                        current_damage_(1) {
};

std::string GameState::getHash(const std::string &data) {
    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(data);

    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
};

FileWrapper& operator<<(FileWrapper& file_wrapper, GameState& state) {
    nlohmann::json json_file;
    nlohmann::json data;
    Serialization ser(data);

    ser.to_json(state.getPlayer().getShipManager(), "player_ship_manager");
    ser.to_json(state.getPlayer().getBoard(), "player_board");
    ser.to_json(state.getPlayer().getAbilityManager(), "player_ability_manager");
    ser.to_json(state.getBot().getShipManager(), "bot_ship_manager");
    ser.to_json(state.getBot().getBoard(), "bot_board");

    std::string json_string = data.dump();

    json_file["data"] = data;
    json_file["hash_value"] = state.getHash(json_string);

    try {
        file_wrapper.write(json_file);
    }
    catch (UnableToOpenFileException& e){
        std::cerr << e.what() << std::endl;
    }

    return file_wrapper;
}

FileWrapper &operator>>(FileWrapper& file_wrapper, GameState &state) {
    nlohmann::json j;

    try {
        file_wrapper.read(j);
    }
    catch (UnableToOpenFileException& e) {
        std::cerr << e.what() << std::endl;
        return file_wrapper;
    }

    nlohmann::json data = j.at("data");
    std::string savedHashValue = j.at("hash_value");

    std::string jsonString = data.dump();

    // if (savedHashValue != state.getHash(jsonString))
    //     throw HashMismatchException();

    // TODO: МЕНЯТЬ КОНСТРУКТОР
    Deserialization deser(data);
    ShipManager ship_manager;
    Board board;
    AbilityManager ability_manager;

    ShipManager bot_ship_manager;
    Board bot_board;

    deser.from_json(ship_manager, "player_ship_manager");
    deser.from_json(board, "player_board");
    deser.from_json(ability_manager, "player_ability_manager");

    deser.from_json(bot_ship_manager, "bot_ship_manager");
    deser.from_json(bot_board, "bot_board");

    state.getPlayer().getShipManager() = ship_manager;
    state.getPlayer().getBoard() = board;
    state.getPlayer().getAbilityManager() = ability_manager;

    state.getBot().getShipManager() = bot_ship_manager;
    state.getBot().getBoard() = bot_board;

    state.placeShips(state.getPlayer().getShipManager(), state.getPlayer().getBoard());
    state.placeShips(state.getBot().getShipManager(), state.getBot().getBoard());

    return file_wrapper;
}

void GameState::placeShips(ShipManager &shipManager, Board &board) {
    for (int i = 0; i < shipManager.getShipCount(); ++i) {
        for (int j = 0; j < shipManager[i].getSize(); ++j) {
            Coord coord = shipManager[i].getSegment(j)->segment_coord;
            Board::Cell &cell = board.getCell(coord);
            cell.segment = shipManager[i].getSegment(j);
        }
    }
}

void GameState::loadGame(const std::string &file) {
    FileWrapper file_wrapper(file);
    file_wrapper >> *this;
}

void GameState::saveGame(const std::string &file) {
    std::ofstream ofs(file, std::ofstream::out | std::ofstream::trunc);
    FileWrapper file_wrapper(file);
    file_wrapper << *this;
}

bool &GameState::getIsAbilityUsed() {
    return this->is_ability_used_cond_;
}

int &GameState::getCurrentDamage() {
    return this->current_damage_;
}

void GameState::setCurrentDamage(int damage) {
    this->current_damage_ = damage;
};

void GameState::setIsAbilityUsed(bool value) {
    this->is_ability_used_cond_ = value;
};

PlayerUnit &GameState::getPlayer() {
    return this->player_;
};

BotUnit &GameState::getBot() {
    return this->bot_;
};

GameState::~GameState() = default;
