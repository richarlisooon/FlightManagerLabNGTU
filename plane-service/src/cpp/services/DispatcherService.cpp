#include "../../header/services/DispatcherService.h"

using namespace std;

list<DispatcherModel> DispatcherService::getAllDispatchers(string token)
{
    set<string> permissions;
    list<DispatcherModel> dispatchers = repo.getDispatchers();
    if (dispatchers.empty())
        permissions.insert("dispatcher-get-public ");
    else {
        string dispatchersId = to_string(dispatchers.front().getId());
        auto it = next(dispatchers.begin());
        for (;it != dispatchers.end(); it++)
            dispatchersId += "," + to_string((*it).getId());
        permissions.insert("dispatcher-get-public " + dispatchersId);
    }
    if (!ident.authorize(permissions, token))
         throw string("401 User is unauthorized");
    return dispatchers;
}

DispatcherModel DispatcherService::getDispatcherById(long int id, string token, bool isPrivate)
{
    set<string> permissions;
    if(isPrivate)
        permissions.insert("dispatcher-get-private " + to_string(id));
    else
        permissions.insert("dispatcher-get-public " + to_string(id));

    list<DispatcherModel> dispatchers = repo.getDispatchers(&id);
    if (!ident.authorize(permissions, token))
         throw string("401 User is unauthorized");
    return dispatchers.front();
}

DispatcherModel DispatcherService::updateDispatcher(DispatcherModel dispatcher, set<string> update, string token)
{
    set<string> permissions;
    if(update.count("password"))
        permissions.insert("dispatcher-update-private " + to_string(dispatcher.getId()));
    else
        permissions.insert("dispatcher-update-public " + to_string(dispatcher.getId()));
    if (!ident.authorize(permissions, token))
         throw string("401 User is unauthorized");
    long int dispId = ident.getIdByToken(token);
    list<DispatcherModel> dispatchers = repo.getDispatchers(&dispId);
    if (!dispatchers.front().getRoles().count(RoleModel::ADMIN))
    {
        if (update.count("isBanned") > 0 || update.count("roles") > 0)
            throw string("401 Update fields not provided for this user");
    }
    DispatcherModel res = repo.updateDispatchers(dispatcher, update);
    return res;
}
