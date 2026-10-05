#include "../include/pin_strength.h"

bool PINStrength::isWeak(const std::string &pin)
{
    if (isRepeated(pin))
        return true;

    if (isAscending(pin))
        return true;

    if (isDescending(pin))
        return true;

    if (isFrequent(pin))
        return true;

    return false;
}

bool PINStrength::isRepeated(const std::string &pin)
{
    for (size_t i = 1; i < pin.length(); i++)
    {
        if (pin[i] != pin[0])
            return false;
    }

    return true;
}

bool PINStrength::isAscending(const std::string &pin)
{
    for (size_t i = 1; i < pin.length(); i++)
    {
        if (pin[i] != pin[i - 1] + 1)
            return false;
    }

    return true;
}

bool PINStrength::isDescending(const std::string &pin)
{
    for (size_t i = 1; i < pin.length(); i++)
    {
        if (pin[i] != pin[i - 1] - 1)
            return false;
    }

    return true;
}

bool PINStrength::isFrequent(const std::string &pin)
{
    int count[10] = {};

    for (char digit : pin)
    {
        count[digit - '0']++;
    }

    for (int i = 0; i < 10; i++)
    {
        if (count[i] >= 4)
            return true;
    }

    return false;
}