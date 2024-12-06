#include "game_state.hpp"

GameState::GameState(PlayerUnit& player, BotUnit& bot): player_(player), bot_(bot) {};

std::string GameState::getHash(const std::string& data) {
    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(data);

    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
};

void GameState::placeShips(ShipManager& shipManager, Board& board) {
    for (int i = 0; i < shipManager.getShipCount(); ++i) {
        for (int j = 0; j < shipManager[i].getSize(); ++j) {
            Coord coordinate = shipManager[i].getSegment(j)->coordinate;
            auto& cell = board.getCell(coordinate);
            cell.segment = shipManager[i].getSegment(j);
        }
    }
}

void GameState::loadGame(const std::string& file) {
    FileWrapper file_wrapper(file);
    file_wrapper >> *this;
}

void GameState::saveGame(const std::string& file) {
    std::ofstream ofs(file, std::ofstream::out | std::ofstream::trunc);
    FileWrapper file_wrapper(file);
    file_wrapper << *this;
}

GameState::~GameState() = default;