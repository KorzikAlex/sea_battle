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
#ifndef SEABATTLE_INCLUDE_EXCEPTIONS_OUT_OF_RANGE_HPP
#define SEABATTLE_INCLUDE_EXCEPTIONS_OUT_OF_RANGE_HPP

#include <exception>
#include <string>

class OutOfRangeException: public std::exception {
public:
    explicit OutOfRangeException (const std::string& message);
    const char* what() const noexcept override;
private:
    std::string message_;
};

#endif // SEABATTLE_INCLUDE_EXCEPTIONS_OUT_OF_RANGE_HPP
