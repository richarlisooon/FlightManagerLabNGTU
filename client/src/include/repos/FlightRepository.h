#pragma once

#include <list>
#include "../models/FlightModel.h"

namespace src
{
    class FlightRepository
    {
    public:
        std::list<FlightModel> getAllFlights(std::string token);
        FlightModel createFlight(FlightModel flight, std::string token);
    };
}