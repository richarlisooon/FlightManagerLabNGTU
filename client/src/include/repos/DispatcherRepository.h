#pragma once
#include "../models/DispatcherModel.h"

#include <list>


namespace src
{
    class DispatcherRepository
    {
    public:
        std::list<DispatcherModel> getDispatchers(std::string token);
        DispatcherModel updateDispatchers(DispatcherModel dispatcher, std::set<std::string> updates, std::string token);
        DispatcherModel getDispatcherById(long int id, std::string token);
    };
}