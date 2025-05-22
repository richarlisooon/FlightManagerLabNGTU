#include "../../include/repos/TimeRepository.h"
#include "../../include/Config.h"

#include <httplib.h>
#include <nlohmann/json.hpp>

using namespace std;
using namespace src;
using namespace httplib;
using namespace nlohmann;

string TimeRepository::getCurrentTime(string token)
{
    Client cli(GATEWAY_HOST_PORT);

    Headers headers = {
        {AUTH_TOKEN_NAME, token}
    };
    auto res = cli.Get(TIME_GET_MAPPING, headers);
    if (res->status >= 200 && res->status < 300)
    {
        auto time = res->body;
        return time;
    }
    throw res->status;
}

bool TimeRepository::addTime(long int time, string token)
{
    Client cli(GATEWAY_HOST_PORT);
    Headers headers = {
        {AUTH_TOKEN_NAME, token}
    };

    Params params = {
        {"skip", to_string(time)}
    };
    auto res = cli.Post(TIME_SKIP_MAPPING, headers, params);
    if (res->status >= 200 && res->status < 300)
        return true;
    throw res->status;
}
