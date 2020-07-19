#pragma once
#include <cstdint>
#include <ostream>
#include <variant>
#include <vector>
#include "Ship.hpp"
#include "Commands.hpp"

struct ShipAndCommands
{
    Ship ship;
    std::vector<std::variant<AccCommand, DetonateCommand, ShootCommand>> appliedCommands;
};

std::ostream& operator<<(std::ostream& os, const ShipAndCommands& ship);

std::ostream& operator<<(std::ostream& os, const std::vector<ShipAndCommands>& ships);
