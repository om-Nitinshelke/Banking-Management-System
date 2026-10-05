#ifndef PIN_STRENGTH_H
#define PIN_STRENGTH_H

#include<string>

class PINStrength {
public:
    bool isWeak(const std::string &pin);

private:
    bool isRepeated(const std::string &pin);
    bool isAscending(const std::string &pin);
    bool isDescending(const std::string &pin);
    bool isFrequent(const std::string &pin);
};



#endif
