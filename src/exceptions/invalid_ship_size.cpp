#include "exceptions/invalid_ship_size.hpp"

InvalidShipSizeException::InvalidShipSizeException(const std::string& message): message_(message){};

const char *InvalidShipSizeException::what() const noexcept {
    return message_.c_str();
}


