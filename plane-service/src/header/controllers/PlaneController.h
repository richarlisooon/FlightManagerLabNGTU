#pragma once
#include "IController.h"
#include "../services/PlaneService.h"
#include "../utils/PlaneLogger.h"

class PlaneController : public IController {
    PlaneLogger log;
    PlaneService serv;
public:
    void configure(httplib::Server* server) override;

};