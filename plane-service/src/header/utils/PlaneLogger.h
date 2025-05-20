#pragma once
#include <string>
class PlaneLogger
{
public:
    void info(std::string inf);
    void debug(std::string debug);
    void warn(std::string warn);
    void error(std::string err);
};
