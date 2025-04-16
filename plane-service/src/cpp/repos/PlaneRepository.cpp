#include "../../header/repos/PlaneRepository.h"
#include "../../Config.h"
#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>

using namespace std;
using namespace httplib;
using namespace nlohmann;
list<PlaneModel> PlaneRepository::getPlanes(long int* id, string* name, string* pilot, int* builtYear, int* brokenPercentage, int* speed, int* minAirportSize)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);


}
PlaneModel PlaneRepository::createPlane(PlaneModel plane)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);


}
bool PlaneRepository::deletePlane(long int id)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);


}
PlaneModel PlaneRepository::updatePlane(PlaneModel plane, set<string> updates)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);


}

