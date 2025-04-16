#pragma once
#include <list>
#include <set>
#include <string>
#include "../models/DispatcherModel.h"

class DispatcherRepository
{
public:
    std::list<DispatcherModel> getDispatchers(long int* id = nullptr, std::string* firstName = nullptr, std::string* lastName = nullptr, std::string* email = nullptr, std::string* password = nullptr, bool* isBanned = nullptr, std::set<RoleModel*>* roles = nullptr);
    DispatcherModel updateDispatchers(DispatcherModel dispatcher, std::set<std::string> update);
};
