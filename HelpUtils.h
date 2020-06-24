#include <string>
#pragma once

unsigned InputUnsigned(std::string msg, unsigned min = 0, unsigned max = UINT_MAX);

bool IsInRange(int number, int low = 0, int max = UINT_MAX);

std::string InputString(std::string msg);

double InputDouble(std::string msg, double min = 0, double max = DBL_MAX);