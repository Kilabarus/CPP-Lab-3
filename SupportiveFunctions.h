#include <string>
#include "DateAndTime.h"
#pragma once

unsigned InputUnsigned(std::string msg, unsigned min = 0, unsigned max = UINT_MAX);

std::string InputString(std::string msg);

std::string CharArrayToString(char* a);