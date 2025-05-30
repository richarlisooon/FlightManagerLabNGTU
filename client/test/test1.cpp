#include "../src/include/srclib.h"
#include <iostream>

using namespace std;
using namespace src;

int main(int argc, char* argv[])
{
    auto token = *(++IdentityRepository().login("email", "pass").begin());
    auto long int currentId = stol(*(++IdentityRepository().login("email", "pass").end()));
    AirportModel airport = AirportRepository().createAirport(AirportModel(0, "name", 10, 0, 0), token);
    AirportModel airport1 = AirportRepository().createAirport(AirportModel(0, "fame", 10, 10000, 10000), token);
    set<string> updateAir;
    updateAir.insert("size");
    updateAir.insert("name");
    AirportRepository().updateAirport(AirportModel(airport.getId(), "name1", 100, 0, 0), updateAir, token);
    AirportRepository().getAllAirports(token);
    DispatcherRepository().getDispatcherById(currentId, token);
    set<string> updateDisp;
    updateDisp.insert("firstName");
    updateDisp.insert("lastName");
    DispatcherRepository().updateDispatchers(DispatcherModel(currentId, "a", "a", "email", "pass", false, set<RoleModel>()), updateDisp, token);
    PlaneModel plane = PlaneRepository().createPlane(PlaneModel(0, "a", "b", 2005, 0, 10, 5), token);
    set<string> updatePlane;
    updatePlane.insert("pilot");
    updatePlane.insert("name");
    updatePlane.insert("builtYear");
    PlaneRepository().getPlanes(token);
    FlightRepository().createFlight(FlightModel(0, 0, 0, 1, plane.getId(), airport1.getId()), token);
    FlightRepository().getAllFlights(token);
    TimeRepository().addTime(2000, token);
    TimeRepository().getCurrentTime(token);
    PlaneRepository().updatePlane(PlaneModel(plane.getId(), "b", "a", 2006, 0, 10, 5), updatePlane, token);
    PlaneRepository().deletePlane(plane.getId(), token);
    AirportRepository().deleteAirport(airport.getId(), token);
    AirportRepository().deleteAirport(airport1.getId(), token);
    return 0;
}

