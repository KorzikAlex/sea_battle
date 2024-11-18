/**
 * @file no_available_abilities.cpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2024-11-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "exceptions/no_available_abilities.hpp"

NoAvailableAbilitiesException::NoAvailableAbilitiesException(const std::string &message): message_(message) {
};

const char *NoAvailableAbilitiesException::what() const noexcept {
    return message_.c_str();
}
