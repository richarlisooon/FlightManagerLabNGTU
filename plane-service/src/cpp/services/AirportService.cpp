#include "../../header/services/AirportService.h"
#include "../../header/services/FlightService.h"
#include <ctime>
using namespace std;
bool AirportSortByTime(FlightModel a, FlightModel b)
{
    return a.getTimestampEnd() > b.getTimestampEnd();
}
list<AirportModel> AirportService::getAllAirports(string token)
{
    set<string> permissions;
    permissions.insert("airport-get");
    if (!ident.authorize(permissions, token))
        throw 401;
    list<AirportModel> airports = repo.getAirports();
    return airports;
}

AirportModel AirportService::createAirport(AirportModel airport, string token)
{
    set<string> permissions;
    permissions.insert("airport-create");
    if (!ident.authorize(permissions, token))
        throw 401;
    AirportModel res = repo.createAirport(airport);
    return res;
}

AirportModel AirportService::updateAirport(AirportModel airport, set<string> update, string token)
{
    set<string> permissions;
    permissions.insert("airport-update");
    if (!ident.authorize(permissions, token))
         throw 401;
    long int airId = airport.getId();
    list<FlightModel> flights = flight.getFlights();
    for (auto fly : flights)
    {
        long int planeId = fly.getPlaneId();
        if (plane.getPlanes(&planeId).empty())
        {
            continue;
        }
        list<FlightModel> flights2 = flight.getFlights(nullptr, nullptr, nullptr, nullptr, &planeId);
        flights2.sort(AirportSortByTime);
        auto it = flights2.begin();
        if (it->getAirportId() == airId)
            throw 409;
        if (flights2.size() > 1)
        {
            if (it->getTimestampEnd() < timer.getAddedTime() + static_cast<long int>(time(nullptr)))
            {
                it++;
                if (it->getAirportId() == airId)
                    throw 409;
            }
        } else
        {
            list<AirportModel> airports = repo.getAirports();
            if (airports.front().getId() == airId)
                throw 409;
        }
    }
    AirportModel res = repo.updateAirport(airport, update);
    return res;
}

bool AirportService::deleteAirport(long int id, string token)
{
    set<string> permissions;
    permissions.insert("airport-delete");
    if (!ident.authorize(permissions, token))
        throw 401;
    list<FlightModel> flights = flight.getFlights();
    for (auto fly : flights)
    {
        long int planeId = fly.getPlaneId();
        if (plane.getPlanes(&planeId).empty())
        {
            continue;
        }
        list<FlightModel> flights2 = flight.getFlights(nullptr, nullptr, nullptr, nullptr, &planeId);
        flights2.sort(AirportSortByTime);
        auto it = flights2.begin();
        if (it->getAirportId() == id)
            throw 409;
        if (it->getTimestampEnd() > timer.getAddedTime() + static_cast<long int>(time(nullptr)))
        {

            if (flights2.size() > 1)
            {
                it++;
                if (it->getAirportId() == id)
                    throw 409;
            } else
            {
                list<AirportModel> airports = repo.getAirports();
                if (airports.front().getId() == id)
                    throw 409;
            }
        }
    }
    bool res = repo.deleteAirport(id);
    return res;
}
