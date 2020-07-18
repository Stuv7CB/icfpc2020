#include <gtest/gtest.h>
#include "Modulation.hpp"

TEST(Modulation, DemodulateList)
{
    std::string_view input = "1101000";
    auto rez = Modulation::demodulateList(input);
    Modulation::printResponse(rez);
    ASSERT_EQ(0, std::get<int64_t>(rez.value[0])) << "Zero parsed";
}

TEST(Modulation, DemodulateList1)
{
    std::string_view input = "110000";
    auto rez = Modulation::demodulateList(input);
    Modulation::printResponse(rez);
}

TEST(Modulation, DemodulateList2)
{
    std::string_view input = "110110000101100010";
    auto rez = Modulation::demodulateList(input);
    Modulation::printResponse(rez);
}

TEST(Modulation, DemodulateList3)
{
    std::string_view input = "1101100001110110001000";
    auto rez = Modulation::demodulateList(input);
    Modulation::printResponse(rez);
}

TEST(Modulation, DemodulateList4)
{
    std::string_view input = "1101100001111101100010110110001100110110010000";
    auto rez = Modulation::demodulateList(input);
    Modulation::printResponse(rez);
}

TEST(Modulation, DemodulateListFinalBoss)
{
    std::string_view input = "11011000011111110101101111111111111111100111010101000"
                             "10010100111011001110101110100001011010111010010110100"
                             "11110110000111011111111111111111001011000100100011100"
                             "10011101010001001010101101111101001100111110000000";
    auto rez = Modulation::demodulateList(input);
    Modulation::printResponse(rez);
}

TEST(Modulation, DemodulateGameStateList)
{
    std::string_view input = "110110000111011000101100110000";
    auto rez = Modulation::demodulateList(input);
    Modulation::printResponse(rez);
}

TEST(Modulation, Modulate)
{
    Modulation::List startRequest;
    startRequest.value = std::vector<std::variant<int64_t, Modulation::List>>
    {
        std::variant<int64_t, Modulation::List>(3),
        std::variant<int64_t, Modulation::List>(3540849226164375841),
        std::variant<int64_t, Modulation::List>(
                    Modulation::List(
                        std::vector<std::variant<int64_t, Modulation::List>>
                        {
                            std::variant<int64_t, Modulation::List>(0),
                            std::variant<int64_t, Modulation::List>(0),
                            std::variant<int64_t, Modulation::List>(0),
                            std::variant<int64_t, Modulation::List>(0),
                        }))
    };

    auto modulated = Modulation::modulateList(startRequest);
    std::string_view mView = modulated;
    auto demodulated = Modulation::demodulateList(mView);
    Modulation::printResponse(demodulated);
}
