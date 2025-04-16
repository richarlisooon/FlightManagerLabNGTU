#include "../../header/repos/FlightRepository.h"
#include <cpp-httplib/httplib.h>
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>

using namespace std;
using namespace httplib;
using namespace nlohmann;
list<FlightModel> FlightRepository::getFlights(long int* id, long int* timestampStart, long int* timestampEnd, long int* dispatcherId, long int* planeId, long int* airportId)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);


}

FlightModel FlightRepository::createFlight(FlightModel flight)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);


}

