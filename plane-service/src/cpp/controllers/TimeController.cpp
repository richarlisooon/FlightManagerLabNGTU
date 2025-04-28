#include "../../header/controllers/TimeController.h"

#include "../../Config.h"
using namespace std;
using namespace httplib;
void TimeController::configure(Server* server)
{
    server->Get(TIME_GET_MAPPING, [this](const Request& req, Response& res)
    {

    });
    server->Post(TIME_SKIP_MAPPING, [this](const Request& req, Response& res)
    {

    });
}

