#include "exceptions/incorrect_ship_position.hpp"

IncorrectShipPositionException::IncorrectShipPositionException(const std::string &message):message_(message) {};

const char *IncorrectShipPositionException::what() const noexcept {
    return message_.c_str();
}

