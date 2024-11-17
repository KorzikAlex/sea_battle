#ifndef SEABATTLE_INCLUDE_EXCEPTIONS_INVALID_SHIP_SIZE_HPP
#define SEABATTLE_INCLUDE_EXCEPTIONS_INVALID_SHIP_SIZE_HPP

#include <exception>
#include <string>

class InvalidShipSizeException: public std::exception {
public:
    explicit InvalidShipSizeException (const std::string& message);
    const char* what() const noexcept override;
private:
    std::string message_;
};

#endif //SEABATTLE_INCLUDE_EXCEPTIONS_INVALID_SHIP_SIZE_HPP
