#pragma once
#include "InvadersError.h"
#include "checkML.h"

class FileNotFoundError : public InvadersError
{
public:
    FileNotFoundError(const std::string& message);
};