#include "../../include/repos/DispatcherRepository.h"
#include "../../include/Config.h"

#include <httplib.h>
#include <nlohmann/json.hpp>

using namespace std;
using namespace src;
using namespace httplib;
using namespace nlohmann;

list<DispatcherModel> DispatcherRepository::getDispatchers(string token)
{
    Client cli(GATEWAY_HOST_PORT);

    Headers headers = {
        {AUTH_TOKEN_NAME, token}
    };
    string role;

    auto res = cli.Get(DISPATCHER_GET_ALL_MAPPING, headers);
    if (res->status >= 200 && res->status < 300)
    {
        json dispatcher_json = json::parse(res->body);
        list<DispatcherModel> result;
        for (auto item : dispatcher_json)
        {
            set<RoleModel> Roles;
            for (auto Role : item["roles"])
            {
                if (Role == "ADMIN")
                    Roles.insert(RoleModel::ADMIN);
                else if (Role == "DISPATCHER")
                    Roles.insert(RoleModel::DISPATCHER);
            }
            DispatcherModel dispatcher(item["id"], item["firstName"], item["lastName"], item["email"], item["password"],
                                       item["isBanned"], Roles);
            result.push_back(dispatcher);
        }
        return result;
    }
    throw res->status;
}

DispatcherModel DispatcherRepository::updateDispatchers(DispatcherModel dispatcher, set<string> updates, string token)
{
    Client cli(GATEWAY_HOST_PORT);

    Headers headers = {
        {AUTH_TOKEN_NAME, token}
    };
    json dispatcher_json;
    dispatcher_json["id"] = dispatcher.getId();
    dispatcher_json["firstName"] = dispatcher.getFirstname();
    dispatcher_json["lastName"] = dispatcher.getLastname();
    dispatcher_json["email"] = dispatcher.getEmail();
    dispatcher_json["password"] = dispatcher.getPassword();
    dispatcher_json["isBanned"] = dispatcher.getIsBanned();
    dispatcher_json["roles"] = json::array();
    for (auto role : dispatcher.getRoles())
    {
        switch (role)
        {
        case RoleModel::ADMIN: dispatcher_json["roles"].push_back("ADMIN");
        case RoleModel::DISPATCHER: dispatcher_json["roles"].push_back("DISPATCHER");
        }
    }
    string update;
    for (auto item : updates)
    {
        if (update.empty())
            update = item;
        else
            update += "," + item;
    }
    auto res = cli.Post(DISPATCHER_UPDATE_MAPPING + "?update=" + update, headers, dispatcher_json.dump(),
                        "application/json");
    if (res->status >= 200 && res->status < 300)
    {
        json dispatcher_hitler = json::parse(res->body);
        set<RoleModel> Roles;
        for (auto Role : dispatcher_hitler["roles"])
        {
            if (Role == "ADMIN")
                Roles.insert(RoleModel::ADMIN);
            else if (Role == "DISPATCHER")
                Roles.insert(RoleModel::DISPATCHER);
        }
        DispatcherModel dispatcher_update(dispatcher_hitler["id"], dispatcher_hitler["firstName"],
                                          dispatcher_hitler["lastName"], dispatcher_hitler["email"],
                                          dispatcher_hitler["password"], dispatcher_hitler["isBanned"], Roles);
        return dispatcher_update;
    }
    throw res->status;
}

DispatcherModel DispatcherRepository::getDispatcherById(long int id, string token)
{
    Client cli(GATEWAY_HOST_PORT);
    Headers headers = {
        {AUTH_TOKEN_NAME, token}
    };

    auto res = cli.Get(DISPATCHER_GET_BY_ID_MAPPING + "?id=" + to_string(id), headers);
    if (res->status >= 200 && res->status < 300)
    {
        json dispatcher_json = json::parse(res->body);

        set<RoleModel> Roles;
        for (auto Role : dispatcher_json["roles"])
        {
            if (Role == "ADMIN")
                Roles.insert(RoleModel::ADMIN);
            else if (Role == "DISPATCHER")
                Roles.insert(RoleModel::DISPATCHER);
        }
        DispatcherModel dispatcher(dispatcher_json["id"], dispatcher_json["firstName"], dispatcher_json["lastName"],
                                   dispatcher_json["email"], dispatcher_json["password"], dispatcher_json["isBanned"],
                                   Roles);


        return dispatcher;
    }
    throw res->status;
}
