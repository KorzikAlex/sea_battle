#include "exceptions/no_available_abilities.hpp"

NoAvailableAbilitiesException::NoAvailableAbilitiesException(const std::string &message): message_(message) {
};

const char *NoAvailableAbilitiesException::what() const noexcept {
    return message_.c_str();
}
