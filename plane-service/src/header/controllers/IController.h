#pragma once
#include <cpp-httplib/httplib.h>

class IController {
public:
    virtual void configure(httplib::Server* server) = 0;
};
