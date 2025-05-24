#pragma once
#include "IController.h"
#include "../services/DispatcherService.h"
#include "../utils/PlaneLogger.h"
class DispatcherController : public IController
{
    PlaneLogger log;
    DispatcherService serv;
public:
    void configure(httplib::Server* server) override;
};