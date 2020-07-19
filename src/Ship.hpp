#pragma once
#include <cstdint>
#include <ostream>
#include <vector>
#include "Vector.hpp"
#include "StaticGameInfo.hpp"
#include <any>

struct Ship
{
    Role role;
    int64_t shipId;
    Vector position;
    Vector velocity;
    std::any x4;
    std::any x5;
    std::any x6;
    std::any x7;
};

std::ostream& operator<<(std::ostream& os, const Ship& ship);

std::ostream& operator<<(std::ostream& os, const std::vector<Ship>& ships);
