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
    explicit FileWrapper(const std::string &file_name);

    void read(nlohmann::json &json_file);

    void write(const nlohmann::json &json_file);

    ~FileWrapper();

private:
    std::fstream file_;
};
