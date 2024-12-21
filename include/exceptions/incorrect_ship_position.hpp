#pragma once
#include <exception>

class IncorrectShipPositionException : public std::exception {
public:
    const char *what() const noexcept override {
        return "Invalid ship placement!";
    }
};
