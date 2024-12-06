/**
 * @file no_available_abilities.hpp
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
#include <string>

class NoAvailableAbilitiesException : public std::exception {
public:
    explicit NoAvailableAbilitiesException(const std::string &message);

    const char *what() const noexcept override;

private:
    std::string message_;
};
