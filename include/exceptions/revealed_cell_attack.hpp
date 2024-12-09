//
// Created by KorzikAlex on 09.12.2024.
//

#pragma once

#include <exception>
#include <string>

class RevealedCellAttackException : public std::exception {
public:
    RevealedCellAttackException(std::string message): message_(message) {}
    const char* what() const noexcept override {
        return message_.c_str();
    }
private:
    std::string message_;
};