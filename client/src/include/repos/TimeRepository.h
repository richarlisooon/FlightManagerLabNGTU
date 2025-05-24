#pragma once
#include <string>
namespace src
{
    class TimeRepository
    {
    public:
        std::string getCurrentTime(std::string token);
        bool addTime(long int time, std::string token);
    };
}