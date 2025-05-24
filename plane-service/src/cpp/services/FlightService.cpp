#include "../../header/services/FlightService.h"
#include <cmath>
#include <ctime>
#include "../../Config.h"
using namespace std;
bool flightSortByTime(FlightModel a, FlightModel b)
{
    return a.getTimestampEnd() > b.getTimestampEnd();
}

list<FlightModel> FlightService::getAllFlights(string token)
{
    set<string> permissions;
    permissions.insert("flight-get");
    if (!ident.authorize(permissions, token))
         throw string("401 User is unauthorized");
    list<FlightModel> flights = repo.getFlights();
    return flights;
}


FlightModel FlightService::createFlight(FlightModel flight, string token)
{
    set<string> permissions;
    permissions.insert("flight-create");
    if (!ident.authorize(permissions, token))
         throw string("401 User is unauthorized");
    long int planeId = flight.getPlaneId();
    long int airId = flight.getAirportId();
    list<PlaneModel> planes = planeRepo.getPlanes(&planeId);
    if (planes.empty())
        throw string("409 No planes for flight");
    if (planes.front().getBrokenPercentage() > 80)
        throw string("409 That plane is broken");
    list<AirportModel> airports = airportRepo.getAirports(&airId);
    if (airports.empty())
        throw string("409 Airport does not exist");
    if (airports.front().getSize() < planes.front().getMinAirportSize())
        throw string("409 Airport too small for this plane");
    double x1 = airports.front().getX();
    double y1 = airports.front().getY();
    list<FlightModel> flights = repo.getFlights(nullptr, nullptr, nullptr, nullptr, &planeId);
    list<AirportModel> airports2;
    if (flights.empty())
        airports2 = airportRepo.getAirports();
    else {
        flights.sort(flightSortByTime);
        if (flights.front().getTimestampEnd() > static_cast<long int>(time(nullptr)) + timer.getAddedTime())
            throw string("409 Plane already in flight");
        long int air2Id = flights.front().getAirportId();
        airports2 = airportRepo.getAirports(&air2Id);
    }
    if (airports2.empty())
        throw string("409 No airports for flight");
    int speed = planes.front().getSpeed();
    double x2 = airports2.front().getX();
    double y2 = airports2.front().getY();
    long int length = lround(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
    long int flightTime = length/speed;
    set<string> update;
    update.insert("brokenPercentage");
    PlaneModel plane = planes.front();
    plane.setBrokenPercentage(plane.getBrokenPercentage() + (flightTime / addingBrokenPercentage));
    if (plane.getBrokenPercentage() + (flightTime / addingBrokenPercentage) > 80)
        throw string("409 Plane is too broken for this flight");
    planeRepo.updatePlane(plane, update);
    flight.setTimestampStart(timer.getAddedTime() + static_cast<long int>(time(nullptr)));
    long int timestampEnd = flight.getTimestampStart() + flightTime;
    flight.setTimestampEnd(timestampEnd);
    FlightModel res = repo.createFlight(flight);
    return res;
}
