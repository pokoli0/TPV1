#pragma once
#include "InvadersError.h"
#include "checkML.h"

class SDLError : public InvadersError
{
public:
    SDLError(const std::string& message);
};