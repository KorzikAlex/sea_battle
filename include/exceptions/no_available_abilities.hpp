#pragma once

#include <exception>

class NoAvailableAbilitiesException : public std::exception {
public:
    const char *what() const noexcept override {
        return "You don't have abilities!";
    }
};
