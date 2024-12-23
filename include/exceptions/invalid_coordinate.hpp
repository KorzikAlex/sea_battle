#pragma once

#include <exception>

class InvalidCoordinateException : public std::exception {
public:
    const char *what() const noexcept override {
        return "Invalid coordinate!";
    }
};
