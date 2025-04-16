#include "../../header/repos/AirportRepository.h"
#include "../../Config.h"
#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;
using namespace httplib;
list<AirportModel> AirportRepository::getAirports(long int* id, string* name, int* size, double* x, double* y)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);

}
AirportModel AirportRepository::createAirport(AirportModel airport)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);

}
AirportModel AirportRepository::updateAirport(AirportModel airport, set<string> updates)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);

}


bool AirportRepository::deleteAirport(long int id)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);


}