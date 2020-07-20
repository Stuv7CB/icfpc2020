#pragma once
#include <string_view>
#include <any>
#include <vector>
#include <variant>



namespace Modulation
{
struct List;
using Node = std::variant<int64_t, List>;
using NodeList = std::vector<Node>;

struct List
{
    List()
    {
    }

    List(NodeList &&v) : value(std::move(v))
    {
    }
    NodeList value;
};

int64_t demodulate(std::string_view &signal);
List demodulateList(std::string_view &signal);
std::string modulate(int64_t value);
std::string modulateList(const List &list);

void printResponse(const Modulation::List& resp);

};
