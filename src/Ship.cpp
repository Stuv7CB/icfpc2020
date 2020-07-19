#include "Ship.hpp"
#include <iterator>

std::ostream &operator<<(std::ostream &os, const Ship &ship)
{
    return os << "{ Ship| "
              << "role: " << ship.role << "; "
              << "shipId: " << ship.shipId << "; "
              << "position: " << ship.position << "; "
              << "velocity: " << ship.velocity << "; "
              << "x4: " << ship.x4 << "; "
              << "x5: " << ship.x5 << "; "
              << "x6: " << ship.x6 << "; "
              << "x7: " << ship.x7 << "}";
};

std::ostream &operator<<(std::ostream &os, const std::vector<Ship> &ships)
{
    os << "[";
    std::copy(ships.begin(), ships.end(), std::ostream_iterator<Ship>(os, ","));
    os << "]";
    return os;
}
