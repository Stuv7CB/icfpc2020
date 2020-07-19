#include <gtest/gtest.h>
#include "BasicOrbitAlgo.hpp"

TEST(OrbitAlgo, test)
{
    BasicOrbitAlgo algo;
    Vector vec = {2, 0};
    ASSERT_EQ(vec, algo.calculateSpeed({0, 31}, {0, 0}));
    ++vec.y;
    ASSERT_EQ(vec, algo.calculateSpeed({0, 30}, {0, 0}));
    ++vec.y;
    ASSERT_EQ(vec, algo.calculateSpeed({0, 29}, {0, 0}));

    vec = {1, -2};
    ASSERT_EQ(vec, algo.calculateSpeed({30, 30}, {0, 0}));
    ASSERT_EQ(vec, algo.calculateSpeed({30, 0}, {0, 0}));

    vec = {-2, -1};
    ASSERT_EQ(vec, algo.calculateSpeed({30, -30}, {0, 0}));
    ASSERT_EQ(vec, algo.calculateSpeed({0, -30}, {0, 0}));

    vec = {-1, 2};
    ASSERT_EQ(vec, algo.calculateSpeed({-30, -30}, {0, 0}));
    ASSERT_EQ(vec, algo.calculateSpeed({-30, 0}, {0, 0}));
}
