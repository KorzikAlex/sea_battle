#ifndef SEABATTLE_INCLUDE_EXCEPTIONS_NO_AVALIABLE_ABILITIES_HPP
#define SEABATTLE_INCLUDE_EXCEPTIONS_NO_AVALIABLE_ABILITIES_HPP

#include <exception>
#include <string>

class NoAvailableAbilitiesException: public std::exception {
public:
    explicit  NoAvailableAbilitiesException (const std::string& message);
    const char* what() const noexcept override;
private:
    std::string message_;
};

#endif //SEABATTLE_INCLUDE_EXCEPTIONS_NO_AVALIABLE_ABILITIES_HPP
