#pragma once
#include "IController.h"
#include "../services/TimeService.h"
#include "../utils/PlaneLogger.h"

class TimeController : public IController {
    PlaneLogger log;
    TimeService serv;
public:
    void configure(httplib::Server* server) override;

};