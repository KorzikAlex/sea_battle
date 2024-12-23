#pragma once

#include <exception>

class InvalidShipSizeException : public std::exception {
public:
    const char *what() const noexcept override {
        return "Invalid ship size! It must be between 1 and 4.";
    }
};
