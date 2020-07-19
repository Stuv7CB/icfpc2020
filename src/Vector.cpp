#include "Vector.hpp"

std::ostream &operator<<(std::ostream &os, const Vector &vector)
{
    return os << "{ Vector|"
              << "x: " << vector.x << "; "
              << "y: " << vector.y << "}";
}
