/**
 * @file incorrect_ship_position.cpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2024-11-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "exceptions/incorrect_ship_position.hpp"

IncorrectShipPositionException::IncorrectShipPositionException(const std::string &message):message_(message) {};

const char *IncorrectShipPositionException::what() const noexcept {
    return this->message_.c_str();
}

