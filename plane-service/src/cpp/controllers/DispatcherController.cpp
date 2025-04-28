#include "../../header/controllers/DispatcherController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>



using namespace nlohmann;
using namespace httplib;
using namespace std;


void DispatcherController::configure(Server* server)
{
    // sample request handlers
    server->Get(DISPATCHER_GET_ALL_MAPPING, [this](const Request& req, Response& res)
    {

    });
    server->Post(DISPATCHER_UPDATE_MAPPING, [&](const Request& req, Response& res)
    {

    });
    server->Get(DISPATCHER_GET_BY_ID_MAPPING, [&](const Request& req, Response& res)
    {

    });
}
