#pragma once

#include "renderer.hpp"
#include "game_state.hpp"

#include "exceptions/no_available_abilities.hpp"
#include "exceptions/invalid_coordinate.hpp"
#include "exceptions/revealed_cell_attack.hpp"

class Game {
public:
    explicit Game(const PlayerUnit &player, const BotUnit &bot, const GameState &game_state, const Renderer& renderer);

    void startGame();

    void doPlayerMove();

    void doBotMove();

    void doPlayerAbility();

    void loadGame(const std::string &file_name);

    void saveGame(const std::string &file_name) const;

    void isGameEnd();

    void resetGame();

    void resetRound();

    ~Game() = default;

private:
    PlayerUnit player_;
    BotUnit bot_;
    GameState game_state_;
    Renderer renderer_;

    bool is_player_win_cond_;
    bool is_bot_win_cond_;
    bool is_game_end_cond_;
};
