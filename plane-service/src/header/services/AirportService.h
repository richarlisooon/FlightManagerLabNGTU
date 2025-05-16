#pragma once
#include <list>
#include <set>
#include <string>
#include "../repos/AirportRepository.h"
#include "../../header/repos/IdentityRepository.h"
#include "../../header/repos/FlightRepository.h"
#include "../../header/services/TimeService.h"
#include "../repos/PlaneRepository.h"

class AirportService
{
    AirportRepository repo;
    IdentityRepository ident;
    FlightRepository flight;
    TimeRepository timer;
    PlaneRepository plane;
public:
    std::list<AirportModel> getAllAirports(std::string token);
    AirportModel updateAirport(AirportModel airport, std::set<std::string> update, std::string token);
    AirportModel createAirport(AirportModel airport, std::string token);
    bool deleteAirport(long int id, std::string token);
};
