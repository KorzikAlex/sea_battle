#pragma once

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "game_state.hpp"
#include "json_modules/deserialization.hpp"
#include "json_modules/serizalization.hpp"

#include "exceptions/unable_to_open_file.hpp"

class FileWrapper {
public:
    FileWrapper(const std::string &file_name);

    ~FileWrapper();

    void read(nlohmann::json &j);

    void write(nlohmann::json &j);

    FileWrapper &operator>>(FileWrapper &file_wrapper, GameState &state);

    FileWrapper &operator<<(FileWrapper &fileWrapper, GameState &state);

private:
    std::fstream file_;
};
