#include "../../header/repos/IdentityRepository.h"
#include "../../Config.h"
#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>

using namespace std;
using namespace httplib;
using namespace nlohmann;
int IdentityRepository::getIdByToken(string token)
{
    Client cli(IDENTITY_SERVICE_HOST_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };

    auto res = cli.Post(IDENTITY_GET_ID_BY_TOKEN_MAPPING ,headers, token,  "application/json");
    if (res->status >= 200 && res->status < 300)
    {
        long int id = stol(res->body);
        return id;
    }
    throw res->status;
}

bool IdentityRepository::authorize(set<string> permissions, string token)
{
    Client cli(IDENTITY_SERVICE_HOST_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    json authorize;
    authorize["permissions"] = json::array();
    for (auto permission : permissions)
        authorize["permissions"].push_back(permission);
    authorize["token"] = token;
    auto res = cli.Post(IDENTITY_AUTHORIZE_MAPPING, headers, authorize.dump(), "application/json");
    if (res->status >= 200 && res->status < 300)
    {
        if (res->body == "true")
            return true;
        if (res->body == "false")
            return false;
    }
    throw res->status;
}

