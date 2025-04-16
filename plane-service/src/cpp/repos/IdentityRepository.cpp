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


}

bool IdentityRepository::authorize(set<string> permissions, string token)
{
    Client cli(IDENTITY_SERVICE_HOST_PORT);


}

