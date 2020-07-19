#include <gtest/gtest.h>
#include "Modulation.hpp"

TEST(ModulationSpec, ModulateNested)
{
    Modulation::List startRequest;
    startRequest.value = std::vector<std::variant<int64_t, Modulation::List>>
    {
        std::variant<int64_t, Modulation::List>(1),
        std::variant<int64_t, Modulation::List>(
                    Modulation::List(
                        std::vector<std::variant<int64_t, Modulation::List>>
                        {
                            std::variant<int64_t, Modulation::List>(2),
                            std::variant<int64_t, Modulation::List>(3),
                        })),
        std::variant<int64_t, Modulation::List>(4)
    };

    auto modulated = Modulation::modulateList(startRequest);

    std::cout << modulated << std::endl;
    ASSERT_EQ("1101100001111101100010110110001100110110010000", modulated);
}

TEST(ModulatedSpec, ModulateNil)
{
    Modulation::Nil startRequest;

    auto modulated = Modulation::modulateNil(startRequest);

    std::cout << modulated << std::endl;
    ASSERT_EQ("00", modulated);
}

TEST(ModulatedSpec, ModulateNilList)
{
    Modulation::List startRequest;
    startRequest.value = std::vector<std::variant<int64_t, Modulation::List>>
    {
        std::variant<int64_t, Modulation::List>(Modulation::List()),
    };

    auto modulated = Modulation::modulateList(startRequest);

    std::cout << modulated << std::endl;
    ASSERT_EQ("110000", modulated);
}

TEST(ModulatedSpec, ModulateElementList)
{
    Modulation::List startRequest;
    startRequest.value = std::vector<std::variant<int64_t, Modulation::List>>
    {
        std::variant<int64_t, Modulation::List>(0),
        std::variant<int64_t, Modulation::List>(Modulation::List()),
    };

    auto modulated = Modulation::modulateList(startRequest);

    std::cout << modulated << std::endl;
    ASSERT_EQ("1101000", modulated);
}

TEST(ModulatedSpec, Modulate2ElementList)
{
    Modulation::List startRequest;
    startRequest.value = std::vector<std::variant<int64_t, Modulation::List>>
    {
        std::variant<int64_t, Modulation::List>(1),
        std::variant<int64_t, Modulation::List>(2),
    };

    auto modulated = Modulation::modulateList(startRequest);

    std::cout << modulated << std::endl;
    ASSERT_EQ("11011000101100010", modulated);
}
