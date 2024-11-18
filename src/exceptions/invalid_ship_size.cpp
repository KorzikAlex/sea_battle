/**
 * @file invalid_ship_size.cpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2024-11-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "exceptions/invalid_ship_size.hpp"

InvalidShipSizeException::InvalidShipSizeException(const std::string& message): message_(message){};

const char *InvalidShipSizeException::what() const noexcept {
    return message_.c_str();
}


