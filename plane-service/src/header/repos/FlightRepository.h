#pragma once
#include <list>
#include <string>
#include "../models/FlightModel.h"

class FlightRepository
{
public:
    std::list<FlightModel> getFlights(long int* id = nullptr, long int* timestampStart = nullptr, long int* timestampEnd = nullptr, long int* dispatcherId = nullptr, long int* planeId = nullptr, long int* airportId = nullptr);
    FlightModel createFlight(FlightModel flight);
};
