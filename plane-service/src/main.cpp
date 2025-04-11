#include <cpp-httplib/httplib.h>
#include "header/controllers/AirportController.h"
#include "Config.h"
#include "header/controllers/DispatcherController.h"
#include "header/controllers/FlightController.h"
#include "header/controllers/PlaneController.h"
#include "header/controllers/TimeController.h"
using namespace std;

int main(int argc, char* argv[])
{
        httplib::Server server;
        AirportController().configure(&server);
        PlaneController().configure(&server);
        DispatcherController().configure(&server);
        FlightController().configure(&server);
        TimeController().configure(&server);
        server.listen(SERVER_HOST, SERVER_PORT);
}

