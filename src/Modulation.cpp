#include "Modulation.hpp"
#include <stdexcept>
#include <cstdint>

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
                result += 1 << (count - i - 1);;
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



std::string Modulation::modulateList(std::vector<std::any> &list)
{

    throw std::runtime_error("Not implemented");
}
