#include "Commands.hpp"
#include <iterator>

std::ostream &operator<<(std::ostream &os, const AccCommand &accCommand)
{
    return os << "{ AccCommand|"
              << "shipId: " << accCommand.shipId << "; "
              << "vector: " << accCommand.vector << "}";
}

std::ostream &operator<<(std::ostream &os, const DetonateCommand &detonateCommand)
{
    return os << "{ DetonateCommand|"
              << "shipId: " << detonateCommand.shipId << "}";
}

std::ostream &operator<<(std::ostream &os, const ShootCommand &shootCommand)
{
    return os << "{ ShootCommand|"
              << "shipId: " << shootCommand.shipId << "; "
              << "vector: " << shootCommand.vector << "; "
              << "x3: " << shootCommand.x3 << "}";
}

std::ostream &operator<<(std::ostream &os, const std::variant<AccCommand, DetonateCommand, ShootCommand> &variant)
{
    return std::visit([&os = os](auto&& arg) -> std::ostream &
    {
        return os << arg;
    }, variant);
}

std::ostream &operator<<(std::ostream &os, const std::vector<std::variant<AccCommand, DetonateCommand, ShootCommand> > &variant)
{
    os << "[";
    std::copy(variant.begin(), variant.end(), std::ostream_iterator<std::variant<AccCommand, DetonateCommand, ShootCommand> >(os, ","));
    os << "]";
    return os;
}
