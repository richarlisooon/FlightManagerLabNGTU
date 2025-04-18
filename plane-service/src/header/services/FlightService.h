#pragma once
#include <list>
#include <set>
#include <string>
#include "../repos/TimeRepository.h"
#include "../repos/AirportRepository.h"
#include "../repos/FlightRepository.h"
#include "../repos/IdentityRepository.h"
#include "../repos/PlaneRepository.h"

class FlightService
{
    TimeRepository timer;
    FlightRepository repo;
    IdentityRepository ident;
    PlaneRepository planeRepo;
    AirportRepository airportRepo;
public:
    std::list<FlightModel> getAllFlights(std::string token);
    FlightModel createFlight(FlightModel flight, std::string token);
};