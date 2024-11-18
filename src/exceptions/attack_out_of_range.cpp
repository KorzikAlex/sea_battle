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
#include "exceptions/attack_out_of_range.hpp"

AttackOutOfRangeException::AttackOutOfRangeException(const std::string &message):message_(message) {};

const char *AttackOutOfRangeException::what() const noexcept {
    return message_.c_str();
}
