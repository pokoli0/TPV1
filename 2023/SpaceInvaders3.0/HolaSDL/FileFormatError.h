#pragma once
#include "InvadersError.h"
#include "checkML.h"

class FileFormatError : public InvadersError
{
public:
    FileFormatError(const std::string& message);
};