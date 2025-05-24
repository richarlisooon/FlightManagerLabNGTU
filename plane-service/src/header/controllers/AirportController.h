#pragma once
#include "IController.h"
#include "../services/AirportService.h"
#include "../utils/PlaneLogger.h"
class AirportController : public IController {
    AirportService serv;
    PlaneLogger log;
public:
    void configure(httplib::Server* server) override;

};
