#pragma once
#include <set>
#include <string>

class IdentityRepository
{
public:
    int getIdByToken(std::string token);
    bool authorize(std::set<std::string> permissions, std::string token);
};
