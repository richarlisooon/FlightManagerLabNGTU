#include "../../include/repos/IdentityRepository.h"
#include "../../include/Config.h"

#include <httplib.h>
#include <nlohmann/json.hpp>

using namespace std;
using namespace src;
using namespace httplib;
using namespace nlohmann;

set<string> IdentityRepository::login(string email, string password)
{
    Client cli(GATEWAY_HOST_PORT);
    json j;
    j["email"] = email;
    j["password"] = password;
    auto res = cli.Post(LOGIN_MAPPING, j.dump(), "application/json");
    if (res->status >= 200 && res->status < 300)
    {
        json jopa = json::parse(res->body);
        set<string> login;
        login.insert(to_string(jopa["id"]));
        login.insert(jopa["token"]);
        return login;
    }
    throw res->status;
}

set<string> IdentityRepository::regist(DispatcherModel dispatcher)
{
    Client cli(GATEWAY_HOST_PORT);
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
            break;
        case RoleModel::DISPATCHER: dispatcher_json["roles"].push_back("DISPATCHER");
            break;
        }
    }
    auto res = cli.Post(REGISTER_MAPPING, dispatcher_json.dump(), "application/json");
    if (res->status >= 200 && res->status < 300)
    {
        json jopa = json::parse(res->body);
        set<string> reg;
        reg.insert(to_string(jopa["id"]));
        reg.insert(jopa["token"]);
        return reg;
    }
    throw res->status;
}

