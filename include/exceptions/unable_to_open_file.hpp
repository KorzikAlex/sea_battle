#pragma once

#include <exception>

class UnableToOpenFileException : public std::exception {
public:
    const char *what() const noexcept override {
        return "Can't open the file!";
    }
};
