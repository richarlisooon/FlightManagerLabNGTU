#pragma once

#include <list>
#include <set>
#include <string>
#include "../models/AirportModel.h"

namespace src
{
    class AirportRepository {
    public:
        std::list<AirportModel> getAllAirports(std::string token);
        AirportModel createAirport(AirportModel airport, std::string token);
        bool deleteAirport(long int id, std::string token);
        AirportModel updateAirport(AirportModel airport, std::set<std::string> update, std::string token);
    };
}