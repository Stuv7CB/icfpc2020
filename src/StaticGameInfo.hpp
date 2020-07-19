#pragma once
#include <cstdint>
#include <ostream>
#include <any>
#include "Modulation.hpp"

enum class Role : int64_t
{
    Attacker = 0,
    Defender = 1
};

std::ostream& operator<<(std::ostream& os, const Role role);

struct StaticGameInfo
{
    std::any x0; // Unknown
    Role role;
    std::any x2; // Unknown
    std::any x3; // Unknown
    std::any x4; // Unknown
};

std::ostream& operator<<(std::ostream& os, const StaticGameInfo& staticGameInfo);
