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

/**
 * @brief CLIParser class for parsing command-line arguments.
 *
 * This class is responsible for interpreting command-line arguments and extracting necessary
 * options such as board dimensions.
 */
class CLIParser {
public:
    /**
     * @brief Constructs a CLIParser object.
     *
     * Parses the command-line arguments to extract relevant options and values such as
     * board dimensions and help instructions.
     *
     * @param argc Number of command-line arguments.
     * @param argv Array of command-line arguments.
     *
     * This constructor initializes the parser with default board dimensions of 10x10.
     * It processes the arguments to update the dimensions if specified.
     */
    CLIParser(int argc, char *argv[]);

    /**
     * @brief Retrieves the width of the board.
     *
     * This method returns the horizontal dimension size (size_x) of the board as specified
     * by the command-line arguments or default configuration.
     *
     * @return The width of the board.
     */
    int getSizeX() const;

    /**
     * @brief Retrieves the height of the board.
     *
     * This method returns the vertical dimension size (size_y) of the board as specified
     * by the command-line arguments or default configuration.
     *
     * @return The height of the board.
     */
    int getSizeY() const;

    /**
     * @brief Destructor for the CLIParser class.
     *
     * This destructor cleans up any resources or memory allocated by the
     * CLIParser instance. Being a default destructor, it relies on the
     * compiler to automatically manage resource deallocation.
     */
    ~CLIParser();

private:
    std::unordered_map<std::string, std::string> options;
    int size_x;
    int size_y;
};

#endif // SEABATTLE_INCLUDE_CLI_PARSER_HPP
