#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

class CLIParser {
public:
    CLIParser(int argc, char *argv[]);

    int getSizeX() const noexcept;

    int getSizeY() const noexcept;

    ~CLIParser() = default;

private:
    std::unordered_map<std::string, std::string> options;
    int size_x;
    int size_y;
};
