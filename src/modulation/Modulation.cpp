#include "Modulation.hpp"
#include "helper.hpp"
#include <stdexcept>
#include <cstdint>
#include <cmath>
#include <iostream>

int64_t Modulation::demodulate(std::string_view &signal)
{
    int64_t result = 0;
    auto getValue = [&result, &signal]()
    {
        uint64_t count = 0;
        for (const char &c : signal)
        {
            if (c == '0')
            {
                break;
            }
            ++count;
        }
        signal = signal.substr(count + 1);
        if (count == 0)
        {
            return;
        }
        count *= 4;
        for (uint64_t i = 0; i < count; ++i)
        {
            if (signal[i] == '1')
            {
                result += static_cast<int64_t>(1) << (count - i - 1);
            }
        }
        signal = signal.substr(count);
    };

    if (signal.substr(0, 2) == "11")
    {
        throw std::runtime_error("Demodulation of a list");
    }
    if (signal[0] == '1')
    {
        signal = signal.substr(2);
        getValue();
        return result * -1;
    }
    else if (signal [1] == '1')
    {
        signal = signal.substr(2);
        getValue();
        return result;
    }
    else
    {
        throw std::runtime_error("Demodulation of a list");
    }
}

Modulation::List Modulation::demodulateList(std::string_view &signal)
{
    Modulation::List list;

    if (signal.substr(0,2) != "11")
    {
        throw std::runtime_error("Not a list");
    }

    while (!signal.empty() && signal.substr(0, 2) == "11")
    {
        signal = signal.substr(2);
        if (signal.substr(0, 2) == "11")
        {
            list.value.emplace_back(demodulateList(signal));
            continue;
        }

        if (signal.substr(0, 2) == "00")
        {
            signal = signal.substr(2);
            list.value.emplace_back(List());
            continue;
        }

        list.value.push_back(demodulate(signal));
    }
    return list;
}

std::string Modulation::modulate(int64_t value)
{
    std::string result;
    if (value >= 0)
    {
        result += "01";
        if (value == 0)
        {
            result += '0';
            return result;
        }
    }
    else
    {
        result += "10";
        value *= -1;
    }
    signed char size = (std::log2(value) / 4.0);
    size += 1;
    result.append(size, '1');
    result += '0';
    size *= 4;
    --size;
    for (; size >= 0; --size)
    {
        if ((value >> size) & 1)
        {
            result += '1';
        }
        else
        {
            result += '0';
        }
    }
    return result;
}

std::string Modulation::modulateList(const List &list)
{
    std::string result;
    for (auto &el : list.value)
    {
        result += "11";
        result += std::visit([](auto&& arg) -> std::string
        {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int64_t>)
            {
                return modulate(arg);
            }
            else if constexpr (std::is_same_v<T, Modulation::List>)
            {
                return modulateList(arg);
            }
            else
            {
                static_assert(always_false_v<T>, "non-exhaustive visitor!");
            }
        }, el);
    }
    result += "00";
    return result;
}

void printResponseArray(const Modulation::List& resp)
{
    std::cout << '(';
    for (auto &el : resp.value)
    {
        std::visit([](auto&& arg)
        {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int64_t>)
            {
                std::cout << arg;
            }
            else if constexpr (std::is_same_v<T, Modulation::List>)
            {
                printResponseArray(arg);
            }
            else
            {
                static_assert(always_false_v<T>, "non-exhaustive visitor!");
            }
        }, el);
        if (&el != &resp.value.back())
        {
            std::cout << ", ";
        }
    }
    std::cout << ')';
}

void Modulation::printResponse(const Modulation::List& resp)
{
    printResponseArray(resp);
    std::cout << "" << std::endl;
}
