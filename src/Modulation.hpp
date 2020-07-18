#pragma once
#include "BigInt.hpp"
#include <string_view>
#include <any>
#include <vector>

class Modulation
{
public:
    static BigInt demodulate(std::string_view &signal);
    static std::vector<std::any> demodulateList(std::string_view &signal);
};
