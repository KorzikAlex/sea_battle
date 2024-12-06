/**
 * @file attack_out_of_range.cpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2024-11-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "exceptions/out_of_range.hpp"

OutOfRangeException::OutOfRangeException(const std::string &message):message_(message) {};

const char *OutOfRangeException::what() const noexcept {
    return this->message_.c_str();
}

