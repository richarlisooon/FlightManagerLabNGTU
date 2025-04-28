#include "../../header/controllers/AirportController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>
#include <string>
#include <sstream>

using namespace nlohmann;
using namespace httplib;
using namespace std;

void AirportController::configure(Server* server)
{
    // sample request handlers
    server->Get(AIRPORT_GET_ALL_MAPPING, [this](const Request& req, Response& res)
    {

    });

    server->Post(AIRPORT_CREATE_MAPPING, [this](const Request& req, Response& res)
    {

    });

    server->Post(AIRPORT_UPDATE_MAPPING, [this](const Request& req, Response& res)
    {

    });

    server->Delete(AIRPORT_DELETE_MAPPING, [this](const Request& req, Response& res)
{

});
}

