#pragma once
#include "IController.h"
#include "../services/AirportService.h"
class AirportController : public IController {
    AirportService serv;
public:
    void configure(httplib::Server* server) override;

};
