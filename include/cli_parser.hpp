/**
 * @file cli_parser.hpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2024-11-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef SEABATTLE_INCLUDE_CLI_PARSER_HPP
#define SEABATTLE_INCLUDE_CLI_PARSER_HPP

#include <string>
#include <unordered_map>

class CLIParser {
public:
    /**
     * @brief Constructor of CLI Parser
     * 
     * @param argc 
     * @param argv 
     */
    CLIParser(int argc, char *argv[]);
    /**
     * @brief Get the width of board
     * 
     * @return int 
     */
    int getSizeX() const;
    /**
     * @brief Get the height of board
     * 
     * @return int 
     */
    int getSizeY() const;

private:
    std::unordered_map<std::string, std::string> options;
    int size_x;
    int size_y;
};

#endif // SEABATTLE_INCLUDE_CLI_PARSER_HPP
