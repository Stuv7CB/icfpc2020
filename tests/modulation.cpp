#include <gtest/gtest.h>
#include "Modulation.hpp"

TEST(Modulation, DemodulateList)
{
    std::string_view input = "1101000";
    auto rez = Modulation::demodulateList(input);
    Modulation::printResponse(rez);
    ASSERT_EQ(0, std::get<int64_t>(rez.value[0])) << "Zero parsed";
}

TEST(Modulation, DemodulateGameStateList)
{
    std::string_view input = "110110000111011000101100110000";
    auto rez = Modulation::demodulateList(input);
    Modulation::printResponse(rez);
}
