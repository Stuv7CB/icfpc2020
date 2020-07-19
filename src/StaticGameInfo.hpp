#pragma once
#include <cstdint>
#include <ostream>

enum class Role : int64_t
{
    Attacker = 0,
    Defender = 1
};

std::ostream& operator<<(std::ostream& os, const Role role)
{
    return os << (role == Role::Attacker ? "Attacker" : "Defender");
}

struct StaticGameInfo
{
    int64_t x0; // Unknown
    Role role;
    int64_t x2; // Unknown
    int64_t x3; // Unknown
    int64_t x4; // Unknown
};

std::ostream& operator<<(std::ostream& os, const StaticGameInfo& staticGameInfo) {
    return os << "{ StaticGameInfo| "
              << "x0: " << staticGameInfo.x0 << "; "
              << "role: " << staticGameInfo.role << "; "
              << "x2: " << staticGameInfo.x2 << "; "
              << "x3: " << staticGameInfo.x3 << "; "
              << "x4: " << staticGameInfo.x4 << "}";
}
