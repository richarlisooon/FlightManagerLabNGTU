#pragma once
#include <list>
#include <set>
#include <string>
#include "../models/PlaneModelResponse.h"
#include "../repos/PlaneRepository.h"
#include "../repos/IdentityRepository.h"
#include "../../header/services/FlightService.h"
#include "../../header/services/AirportService.h"
#include "../../header/services/TimeService.h"
class PlaneService
{
    FlightRepository flight;
    AirportRepository air;
    TimeRepository timer;
    PlaneRepository repo;
    IdentityRepository ident;
public:
    std::list<PlaneModelResponse> getAllPlanes(std::string token);
    PlaneModel createPlane(PlaneModel plane, std::string token);
    bool deletePlane(long int id, std::string token);
    PlaneModel updatePlane(PlaneModel plane, std::set<std::string> update, std::string token);
};
