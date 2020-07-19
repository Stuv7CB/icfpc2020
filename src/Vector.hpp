#pragma once
#include <cstdint>
#include <ostream>
#include <any>

struct Vector
{
    int64_t x;
    int64_t y;
};

static std::ostream &operator<<(std::ostream &os, const std::any &role)
{
    return os << "<unknown>";
}

std::ostream &operator<<(std::ostream &os, const Vector &role);
