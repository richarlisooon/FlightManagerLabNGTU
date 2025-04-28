#include "../../header/controllers/PlaneController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>

using namespace nlohmann;
using namespace httplib;
using namespace std;

void PlaneController::configure(Server* server)
{
    server->Get(PLANE_GET_ALL_MAPPING, [this](const Request& req, Response& res)
    {

    });

    server->Post(PLANE_CREATE_MAPPING, [&](const Request& req, Response& res)
    {

    });
    server->Post(PLANE_UPDATE_MAPPING, [&](const Request& req, Response& res)
    {

    });
    server->Delete(PLANE_DELETE_MAPPING, [&](const Request& req, Response& res)
    {

    });
}
