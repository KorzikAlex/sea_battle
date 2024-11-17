#include "exceptions/attack_out_of_range.hpp"

AttackOutOfRangeException::AttackOutOfRangeException(const std::string &message):message_(message) {};

const char *AttackOutOfRangeException::what() const noexcept {
    return message_.c_str();
}

