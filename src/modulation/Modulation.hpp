#pragma once
#include <string_view>
#include <any>
#include <vector>
#include <variant>

namespace Modulation
{

struct List
{
    List()
    {

    }

    List(std::vector<std::variant<int64_t, List>> &&v) : value(std::move(v))
    {

    }

    std::vector<std::variant<int64_t, List>> value;
};

int64_t demodulate(std::string_view &signal);
List demodulateList(std::string_view &signal);
std::string modulate(int64_t value);
std::string modulateList(const List &list);

void printResponse(const Modulation::List& resp);

};
