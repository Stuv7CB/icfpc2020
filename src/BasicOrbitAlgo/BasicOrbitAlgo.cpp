#include "BasicOrbitAlgo.hpp"
#define M_PI 3.14159265358979323846
#include <cmath>

BasicOrbitAlgo::BasicOrbitAlgo(Vector initialShipCoords,
                               Vector initialShipVelocity)
    : _shipCoords(initialShipCoords), _shipVelocity(initialShipVelocity)
{
}

Vector rotate(double rorationAngle, Vector coords)
{
    if (rorationAngle == 0)
    {
        return coords;
    }
    double rad = rorationAngle * M_PI / 180;
    auto x = std::round(coords.x * cos(rad) - coords.y * sin(rad));
    auto y = std::round(coords.y * cos(rad) + coords.x * sin(rad));
    return {static_cast<int64_t>(x), static_cast<int64_t>(y)};
}

Vector BasicOrbitAlgo::calculateSpeed(Vector currentShipCoords,
                                      Vector currentShipVelocity)
{
    double rorationAngle;
    auto rotate45Coords = rotate(-45, currentShipCoords);

    if (rotate45Coords.x >= 0)
    {
        if(rotate45Coords.y > 0)
        {
            rorationAngle = 0;
        }
        else if(rotate45Coords.y < 0)
        {
            if (rotate45Coords.x != 0)
            {
                rorationAngle = 90;
            }
            else
            {
                rorationAngle = 180;
            }
        }
        else
        {
            rorationAngle = 90;
        }
    }
    else
    {
        if (rotate45Coords.y >= 0)
        {
            rorationAngle = -90;
        }
        else
        {
            rorationAngle = 180;
        }
    }
    auto rotatedCoords = rotate(rorationAngle, currentShipCoords);
    auto rotatedVelocity = rotate(rorationAngle, currentShipVelocity);
    Vector newSpeed;

    if (rotatedCoords.y < _maintainingOrbit)
    {
        newSpeed.y  = _gravity * 2;
    }
    else if (rotatedCoords.y > _maintainingOrbit)
    {
        if (rotatedVelocity.y > 2)
        {
            newSpeed.y = _gravity;
        }
        else
        {
            newSpeed.y = 0;
        }
    }
    else
    {
        newSpeed.y = _gravity;
    }
    newSpeed.x = _gravity * 2 - rotatedVelocity.x;
    return rotate(rorationAngle * -1, newSpeed);
}

int64_t BasicOrbitAlgo::orbit() const
{
    return _maintainingOrbit;
}
