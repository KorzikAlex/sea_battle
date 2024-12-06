#include "game_state.hpp"

GameState::GameState(PlayerUnit& player, BotUnit& bot): player_(player), bot_(bot) {};

GameState::~GameState() = default;