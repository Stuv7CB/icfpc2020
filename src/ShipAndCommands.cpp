#include "ShipAndCommands.hpp"
#include <iterator>

std::ostream &operator<<(std::ostream &os, const ShipAndCommands &ship)
{
    return os << "{ ShipAndCommands| "
              << "ship: " << ship.ship << "; "
              << "appliedCommands: " << ship.appliedCommands << "}";
}

std::ostream &operator<<(std::ostream &os, const std::vector<ShipAndCommands> &ships)
{
    os << "[";
    std::copy(ships.begin(), ships.end(), std::ostream_iterator<ShipAndCommands>(os, ","));
    os << "]";
    return os;
}
