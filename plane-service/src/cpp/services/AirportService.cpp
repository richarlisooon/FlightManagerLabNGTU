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
        throw string("401 User is unauthorized");
    list<AirportModel> airports = repo.getAirports();
    return airports;
}

AirportModel AirportService::createAirport(AirportModel airport, string token)
{
    set<string> permissions;
    permissions.insert("airport-create");
    if (!ident.authorize(permissions, token))
        throw string("401 User is unauthorized");
    AirportModel res = repo.createAirport(airport);
    return res;
}

AirportModel AirportService::updateAirport(AirportModel airport, set<string> update, string token)
{
    set<string> permissions;
    permissions.insert("airport-update");
    if (!ident.authorize(permissions, token))
         throw string("401 User is unauthorized");
    long int airId = airport.getId();

    list<AirportModel> allAirports = repo.getAirports();
    list<PlaneModel> allPlanes = plane.getPlanes();
    long currentTime = timer.getAddedTime() + static_cast<long int>(time(nullptr));

    for (PlaneModel plane1 : allPlanes) {
        long int planeId = plane1.getId();
        list<FlightModel> planeFlights = flight.getFlights(nullptr, nullptr, nullptr, nullptr, &planeId);
        if (planeFlights.empty() && (airId == allAirports.front().getId()))
            throw string("409 Cannot update airport with planes currently present");
        if (!planeFlights.empty()) {
            planeFlights.sort(AirportSortByTime);
            FlightModel lastFlight = planeFlights.front();
            if (lastFlight.getAirportId() == airId && lastFlight.getTimestampEnd() > currentTime) {
                throw string("409 Cannot update airport with planes currently present");
            }
        }
    }
    list<FlightModel> flights = flight.getFlights();
    if (!flights.empty()) {
        for (auto fly: flights) {
            long int planeId = fly.getPlaneId();
            if (plane.getPlanes(&planeId).empty()) {
                continue;
            }
            list<FlightModel> flights2 = flight.getFlights(nullptr, nullptr, nullptr, nullptr, &planeId);
            flights2.sort(AirportSortByTime);
            auto it = flights2.begin();
            if (it->getAirportId() == airId)
                throw string("409 Cannot update airport with planes currently present");
            if (flights2.size() > 1) {
                if (it->getTimestampEnd() < timer.getAddedTime() + static_cast<long int>(time(nullptr))) {
                    it++;
                    if (it->getAirportId() == airId)
                        throw string("409 Airport participates in the flight");
                }
            } else {
                list<AirportModel> airports = repo.getAirports();
                if (airports.front().getId() == airId)
                    throw string("409 Airport participates in the flight");
            }
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
        throw string("401 User is unauthorized");
    list<AirportModel> allAirports = repo.getAirports();
    list<AirportModel> airport = repo.getAirports(&id);
    list<PlaneModel> allPlanes = plane.getPlanes();
    long currentTime = timer.getAddedTime() + static_cast<long int>(time(nullptr));

    for (PlaneModel plane1 : allPlanes) {
        long int planeId = plane1.getId();
        list<FlightModel> planeFlights = flight.getFlights(nullptr, nullptr, nullptr, nullptr, &planeId);
        if (planeFlights.empty() && (airport.front().getId() == allAirports.front().getId()))
            throw string("409 Cannot delete airport with planes currently present");
        if (!planeFlights.empty()) {
            planeFlights.sort(AirportSortByTime);
            FlightModel lastFlight = planeFlights.front();
            if (lastFlight.getAirportId() == id && lastFlight.getTimestampEnd() > currentTime) {
                throw string("409 Cannot delete airport with planes currently present");
            }
        }
    }
    list<FlightModel> flights = flight.getFlights();
    if (!flights.empty()) {
        for (auto fly: flights) {
            long int planeId = fly.getPlaneId();
            if (plane.getPlanes(&planeId).empty()) {
                continue;
            }
            list<FlightModel> flights2 = flight.getFlights(nullptr, nullptr, nullptr, nullptr, &planeId);
            flights2.sort(AirportSortByTime);
            auto it = flights2.begin();
            if (it->getAirportId() == id)
                throw string("409 Cannot delete airport with planes currently present");
            if (it->getTimestampEnd() > timer.getAddedTime() + static_cast<long int>(time(nullptr))) {

                if (flights2.size() > 1) {
                    it++;
                    if (it->getAirportId() == id)
                        throw string("409 Airport participates in the flight");
                } else {
                    list<AirportModel> airports = repo.getAirports();
                    if (airports.front().getId() == id)
                        throw string("409 Airport participates in the flight");
                }
            }
        }
    }
    list<PlaneModel> planes = plane.getPlanes();

    bool res = repo.deleteAirport(id);
    return res;
}
