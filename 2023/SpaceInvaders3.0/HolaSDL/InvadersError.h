#pragma once
#include "checkML.h"

#include <stdexcept>

class InvadersError : public std::logic_error
{
protected:
    std::string m;
public:
    InvadersError(const std::string& message);
    char const* what() const override;
};