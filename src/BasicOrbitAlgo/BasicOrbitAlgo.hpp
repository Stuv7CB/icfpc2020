#pragma once
#include <cstdint>
#include <utility>
#include "Vector.hpp"

class BasicOrbitAlgo
{
public:
    BasicOrbitAlgo(){}
    BasicOrbitAlgo(Vector initialShipCoords,
                   Vector initialShipVelocity);

    Vector calculateSpeed(Vector currentShipCoords,
                          Vector currentShipVelocity);
    int64_t orbit() const;

private:
    Vector _shipCoords;
    Vector _shipVelocity;

    int64_t _maintainingOrbit{30};
    int64_t _gravity{1};
};
