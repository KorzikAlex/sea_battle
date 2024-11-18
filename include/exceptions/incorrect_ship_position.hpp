/**
 * @file incorrect_ship_position.hpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2024-11-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef SEABATTLE_INCLUDE_EXCEPTIONS_INCORRECT_SHIP_POSITION_HPP
#define SEABATTLE_INCLUDE_EXCEPTIONS_INCORRECT_SHIP_POSITION_HPP

#include <exception>
#include <string>

class IncorrectShipPositionException: public std::exception {
public:
    explicit IncorrectShipPositionException (const std::string& message);
    const char* what() const noexcept override;
private:
    std::string message_;
};

#endif //SEABATTLE_INCLUDE_EXCEPTIONS_INCORRECT_SHIP_POSITION_HPP
