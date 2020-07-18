#include "Modulation.hpp"
#include <stdexcept>
#include <cstdint>
#include <cmath>

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

std::vector<std::any> Modulation::demodulateList(std::string_view &signal)
{
    std::vector<std::any> result;

    while (!signal.empty() && signal.substr(0, 2) == "11")
    {
        signal = signal.substr(2);
        if (signal.substr(0, 2) == "11")
        {
            result.emplace_back(demodulateList(signal));
            continue;
        }
        result.push_back(demodulate(signal));

        if (signal.substr(0, 2) == "00")
        {
            signal = signal.substr(2);
            break;
        }
    }
    return result;
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
    for (signed char i = 0; i < size; ++i)
    {
        result += '1';
    }
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

std::string Modulation::modulateList(const std::vector<std::any> &list)
{
    std::string result;
    for (auto &el : list)
    {
        result += "11";
        if (typeid(int64_t) == el.type())
        {
            result += modulate(std::any_cast<int64_t>(el));
        }
        if (typeid(std::vector<std::any>) == el.type())
        {
            result += modulateList(std::any_cast<std::vector<std::any>>(el));
        }
    }
    result += "00";
    return result;
}
