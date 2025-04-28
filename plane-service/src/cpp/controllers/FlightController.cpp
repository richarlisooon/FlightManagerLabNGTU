#include "../../header/controllers/FlightController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>



using namespace nlohmann;
using namespace httplib;
using namespace std;


void FlightController::configure(Server* server)
{
    // sample request handlers
    server->Get(FLIGHT_GET_ALL_MAPPING, [this](const Request& req, Response& res)
    {

    });
    server->Post(FLIGHT_CREATE_MAPPING, [&](const Request& req, Response& res)
    {

    });
}