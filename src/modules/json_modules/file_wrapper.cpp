#include "json_modules/file_wrapper.hpp"

FileWrapper::FileWrapper(const std::string& file_name): file_(file_name) {
}

FileWrapper::~FileWrapper() {
    if (this->file_.is_open()) this->file_.close();
}

void FileWrapper::read(nlohmann::json& j) {
    if (!this->file_.is_open() || !this->file_.good())
        throw UnableToOpenFileException("Can't read the file!");
    this->file_ >> j;
}

void FileWrapper::write(nlohmann::json& j) {
    if (!this->file_.is_open() || !this->file_.good())
        throw UnableToOpenFileException("Can't write the file!");
    this->file_ << j.dump(4);
}

FileWrapper& operator<<(FileWrapper& fileWrapper, GameState& state) {
    nlohmann::json j;
    nlohmann::json data;
    Serialization seri(data);

    seri.to_json(state.getPlayer().getShipManager(), "player_ship_manager");
    seri.to_json(state.getPlayer().getBoard(), "player_board");
    seri.to_json(state.getPlayer().getAbilityManager(), "playerAbilityManager");
    seri.to_json(state.getBot().getShipManager(), "botShipManager");
    seri.to_json(state.getBot().getBoard(), "botField");

    std::string jsonString = data.dump();

    j["data"] = data;
    j["hashValue"] = state.getHash(jsonString);

    try {
        fileWrapper.write(j);
    }
    catch (UnableToOpenFileException& e){
        std::cerr << e.what() << std::endl;
    }

    return fileWrapper;
}

FileWrapper& operator>>(FileWrapper& fileWrapper, GameState& state) {
    nlohmann::json j;

    try {
        fileWrapper.read(j);
    }
    catch (UnableToOpenFileException& e) {
        std::cerr << e.what() << std::endl;
        return fileWrapper;
    }


    nlohmann::json data = j.at("data");
    std::string savedHashValue = j.at("hashValue");

    std::string jsonString = data.dump();

    if (savedHashValue != state.getHash(jsonString)) {
        throw HashMismatchException();
    }

    Deserialization deseri(data);
    ShipManager ship_manager;
    Board board;
    AbilityManager ability_manager;

    ShipManager enemyShipManager;
    Board enemyField;

    deseri.from_json(ship_manager, "player_ship_manager");
    deseri.from_json(board, "player_board");
    deseri.from_json(ability_manager, "playerAbilityManager");

    deseri.from_json(enemyShipManager, "botShipManager");
    deseri.from_json(enemyField, "botField");

    state.getPlayer().getShipManager() = ship_manager;
    state.getPlayer().getBoard() = board;
    state.getPlayer().getAbilityManager() = ability_manager;

    state.getBot().getShipManager() = enemyShipManager;
    state.getBot().getBoard() = enemyField;

    state.placeShips(state.getPlayer().getShipManager(), state.getPlayer().getBoard());
    state.placeShips(state.getBot().getShipManager(), state.getBot().getBoard());

    return fileWrapper;
}