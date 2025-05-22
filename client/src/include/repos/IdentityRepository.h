#pragma once

#include "../models/DispatcherModel.h"

namespace src
{
    class IdentityRepository
    {
    public:
        std::set<std::string> login(std::string email, std::string password);
        std::set<std::string> regist(DispatcherModel dispatcher);
    };
}