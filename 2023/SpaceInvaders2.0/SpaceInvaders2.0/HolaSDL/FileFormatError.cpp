#include "FileFormatError.h"
FileFormatError::FileFormatError(const std::string& message) : InvadersError(message) { m = message; }