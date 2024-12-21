#pragma once

#include <exception>

class RevealedCellAttackException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Cell is already revealed!";
    }
};