# pragma once

#include <exception>
#include <string>

class UnableToOpenFileException: public std::exception {
public:
    explicit UnableToOpenFileException (const std::string& message);
    const char* what() const noexcept override;
private:
    std::string message_;
};