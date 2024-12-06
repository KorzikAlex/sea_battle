#include "exceptions/unable_to_open_file.hpp"

UnableToOpenFileException::UnableToOpenFileException(const std::string &message): message_(message) {
}

const char *UnableToOpenFileException::what() const noexcept {
    return this->message_.c_str();
}
