#include "game_state.hpp"

GameState::GameState(PlayerUnit &player, BotUnit &bot): player_(player), bot_(bot) {
}

std::string GameState::getHash(const std::string &data) const noexcept {
    constexpr std::hash<std::string> hash_fn;
    const size_t hash = hash_fn(data);

    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}

FileWrapper &operator<<(FileWrapper &file_wrapper, const GameState &state) {
    nlohmann::json json_file;
    nlohmann::json data;
    Serialization ser(data);

    ser.to_json(state.getPlayer().getShipManager(), "player_ship_manager");
    ser.to_json(state.getPlayer().getBoard(), "player_board");
    ser.to_json(state.getPlayer().getAbilityManager(), "player_ability_manager");

    ser.to_json(state.getBot().getShipManager(), "bot_ship_manager");
    ser.to_json(state.getBot().getBoard(), "bot_board");

    const std::string json_string = data.dump();

    json_file["data"] = data;
    json_file["hash_value"] = state.getHash(json_string);

    try {
        file_wrapper.write(json_file);
    } catch (UnableToOpenFileException &e) {
        std::cerr << e.what() << std::endl;
    }
    return file_wrapper;
}

FileWrapper &operator>>(FileWrapper &file_wrapper, GameState &state) {
    nlohmann::json json_file;
    try {
        file_wrapper.read(json_file);
    } catch (UnableToOpenFileException &e) {
        std::cerr << e.what() << std::endl;
        return file_wrapper;
    }

    nlohmann::json data = json_file["data"];
    const std::string savedHashValue = json_file["hash_value"];

    if (const std::string jsonString = data.dump();
        savedHashValue != state.getHash(jsonString))
        throw HashMismatchException();

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
            const Coord coord = shipManager[i].getSegment(j)->coord;
            Board::Cell &cell = board.getCell(coord);
            cell.segment = shipManager[i].getSegment(j);
        }
    }
}

void GameState::loadGame(const std::string &file_name) {
    FileWrapper file_wrapper(file_name);
    file_wrapper >> *this;
}

void GameState::saveGame(const std::string &file_name) const {
    std::ofstream ofs(file_name, std::ofstream::out | std::ofstream::trunc);
    FileWrapper file_wrapper(file_name);
    file_wrapper << *this;
}

PlayerUnit &GameState::getPlayer() const noexcept {
    return this->player_;
};

BotUnit &GameState::getBot() const noexcept {
    return this->bot_;
};
