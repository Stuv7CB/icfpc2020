#pragma once
#include <ostream>
#include <cstdint>
#include <variant>
#include <vector>
#include <any>

#include "Vector.hpp"

struct AccCommand
{
    const int64_t commandId = 0;
    int64_t shipId;
    Vector vector;
};

std::ostream& operator<<(std::ostream& os, const AccCommand &accCommand);

struct DetonateCommand
{
    const int64_t commandId = 1;
    int64_t shipId;
};

std::ostream& operator<<(std::ostream& os, const DetonateCommand &detonateCommand);

struct ShootCommand
{
    const int64_t commandId = 2;
    int64_t shipId;
    Vector vector;
    std::any x3; // Unknown
};

std::ostream& operator<<(std::ostream& os, const ShootCommand &shootCommand);

std::ostream& operator<<(std::ostream& os, const std::variant<AccCommand, DetonateCommand, ShootCommand> &variant);

std::ostream& operator<<(std::ostream& os, const std::vector<std::variant<AccCommand, DetonateCommand, ShootCommand>> &variant);
