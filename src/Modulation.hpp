#pragma once
#include <string_view>
#include <any>
#include <vector>

class Modulation
{
public:
    static int64_t demodulate(std::string_view &signal);
    static std::vector<std::any> demodulateList(std::string_view &signal);
};
