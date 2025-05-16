#pragma once
#include <list>
#include <set>
#include <string>
#include "../repos/DispatcherRepository.h"
#include "../repos/IdentityRepository.h"

class DispatcherService
{
    DispatcherRepository repo;
    IdentityRepository ident;
public:
    std::list<DispatcherModel> getAllDispatchers(std::string token);
    DispatcherModel getDispatcherById(long int id, std::string token, bool isPrivate);
    DispatcherModel updateDispatcher(DispatcherModel dispatcher, std::set<std::string> update, std::string token);
};