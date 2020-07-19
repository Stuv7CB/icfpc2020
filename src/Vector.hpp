#pragma once
#include <cstdint>
#include <ostream>

struct Vector
{
    int64_t x;
    int64_t y;
};

std::ostream &operator<<(std::ostream &os, const Vector &role);
