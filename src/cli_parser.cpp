/**
 * @file cli_parser.cpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2024-11-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "cli_parser.hpp"

#include <iostream>

CLIParser::CLIParser(int argc, char **argv): size_x(10), size_y(10) {
    // getting flags and options
    for (int i = 1; i < argc; ++i) {
        if (std::string arg = argv[i]; arg[0] == '-') {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                this->options[arg] = argv[i + 1];
                ++i;
            } else this->options[arg] = "";
        }
    }
    // flags handling
    for (const auto &option: options) {
        if (option.first == "--size_x" && option.second != "")
            this->size_x = std::stoi(option.second); // set size_x of board from parser
        else if (option.first == "--size_y" && option.second != "")
            this->size_y = std::stoi(option.second); // set size_y of board from parser
        if (option.first == "--help" || option.first == "-h") { // get help and exit the game
            std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "--size_x:" << " [<int> arg] " << "set width size of board" << std::endl;
            std::cout << "--size_y:" << " [<int> arg] " << "set height size of board" << std::endl;
            std::cout << "--help: " << "get information about program" << std::endl;
            std::cout << std::endl;
            exit(EXIT_SUCCESS);
        }
    }
}

int CLIParser::getSizeX() const {
    return this->size_x; // get size_x from parser
}

int CLIParser::getSizeY() const {
    return this->size_y; // get size_y from parser
}

CLIParser::~CLIParser() = default;
