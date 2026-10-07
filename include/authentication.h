#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>
#include <unordered_map>
#include <vector>

bool Login(std::unordered_map<int, std::vector<std::string>> &mp);

bool activate(
    std::unordered_map<int, std::vector<std::string>>::iterator &it
);
#endif // AUTHENTICATION_H