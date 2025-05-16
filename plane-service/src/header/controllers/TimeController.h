#pragma once
#include "IController.h"
#include "../services/TimeService.h"

class TimeController : public IController {
    TimeService serv;
public:
    void configure(httplib::Server* server) override;

};