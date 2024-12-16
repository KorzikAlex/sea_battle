/**
 * @file invalid_ship_size.hpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2024-11-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <exception>

class InvalidShipSizeException : public std::exception {
public:
    const char *what() const noexcept {
        return "Invalid ship size. It must be between 1 and 4.";
    }
};
