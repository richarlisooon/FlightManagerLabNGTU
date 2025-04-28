#pragma once
#include "IController.h"
#include "../services/PlaneService.h"

class PlaneController : public IController {
    PlaneService serv;
public:
    void configure(httplib::Server* server) override;

};