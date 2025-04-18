#pragma once
#include "../repos/TimeRepository.h"
#include "../repos/IdentityRepository.h"

class TimeService
{
    TimeRepository repo;
    IdentityRepository ident;
public:
    long int getCurrentTime(std::string token);
    void skipTime(long int addedTime, std::string token);
};
