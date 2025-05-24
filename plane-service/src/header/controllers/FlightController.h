#pragma once
#include "IController.h"
#include "../utils/PlaneLogger.h"
#include "../services/FlightService.h"

class FlightController : public IController
{
    PlaneLogger log;
    FlightService serv;
public:
    void configure(httplib::Server* server) override;
};