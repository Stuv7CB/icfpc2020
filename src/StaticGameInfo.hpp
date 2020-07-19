#pragma once
#include <cstdint>
#include <ostream>
#include "Modulation.hpp"

enum class Role : int64_t
{
    Attacker = 0,
    Defender = 1
};

std::ostream& operator<<(std::ostream& os, const Role role);

struct StaticGameInfo
{
    int64_t x0; // Unknown
    Role role;
    int64_t x2; // Unknown
    int64_t x3; // Unknown
    int64_t x4; // Unknown
};

std::ostream& operator<<(std::ostream& os, const StaticGameInfo& staticGameInfo);
