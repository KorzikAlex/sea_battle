/**
 * @file out_of_range.hpp
 * @author KorzikAlex (alek.korshkov@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2024-11-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
# pragma once

#include <exception>
#include <string>

class OutOfRangeException: public std::exception {
public:
    explicit OutOfRangeException (const std::string& message);
    const char* what() const noexcept override;
private:
    std::string message_;
};
