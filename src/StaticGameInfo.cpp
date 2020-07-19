#include "StaticGameInfo.hpp"

std::ostream &operator<<(std::ostream &os, const Role role)
{
    return os << (role == Role::Attacker ? "Attacker" : "Defender");
}

std::ostream &operator<<(std::ostream &os, const StaticGameInfo &staticGameInfo) {
    return os << "{ StaticGameInfo| "
              << "x0: " << staticGameInfo.x0 << "; "
              << "role: " << staticGameInfo.role << "; "
              << "x2: " << staticGameInfo.x2 << "; "
              << "x3: " << staticGameInfo.x3 << "; "
              << "x4: " << staticGameInfo.x4 << "}";
}
