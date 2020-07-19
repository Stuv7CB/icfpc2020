#pragma once
#include <cstdint>
#include <ostream>
#include <vector>
#include "Vector.hpp"
#include "StaticGameInfo.hpp"

struct Ship
{
    Role role;
    int64_t shipId;
    Vector position;
    Vector velocity;
    int64_t x4;
    int64_t x5;
    int64_t x6;
    int64_t x7;
};

std::ostream& operator<<(std::ostream& os, const Ship& ship);

std::ostream& operator<<(std::ostream& os, const std::vector<Ship>& ships);
