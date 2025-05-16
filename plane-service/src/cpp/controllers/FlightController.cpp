#include "../../header/controllers/FlightController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>



using namespace nlohmann;
using namespace httplib;
using namespace std;


void FlightController::configure(Server* server)
{
    // sample request handlers
    server->Get(FLIGHT_GET_ALL_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE) {
                throw 403;
            }
            list<FlightModel> flights = serv.getAllFlights(header);
            json flights_json = json::array();
            for (auto flight : flights)
            {
                json flight_json;
                flight_json["id"] = flight.getId();
                flight_json["timestampStart"] = flight.getTimestampStart();
                flight_json["timestampEnd"] = flight.getTimestampEnd();
                flight_json["dispatcherId"] = flight.getDispatcherId();
                flight_json["planeId"] = flight.getPlaneId();
                flight_json["airportId"] = flight.getAirportId();
                flights_json.push_back(flight_json);
            }
            res.status = 200;
            res.set_content(flights_json.dump(), "application/json");
        } catch (int& e)
        {
            res.status = e;
        } catch (const exception& e)
        {
            string str(e.what());
            res.status = 500;
        } catch (...)
        {
            res.status = 500;
        }
    });
    server->Post(FLIGHT_CREATE_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE) {
                throw 403;
            }
            json request;
            try
            {
                request = json::parse(req.body);
            } catch (...)
            {
                throw 400;
            }
            long int dispatcherId, planeId, airportId;
            try
            {
                dispatcherId = request["dispatcherId"];
                planeId = request["planeId"];
                airportId = request["airportId"];
            } catch (...)
            {
                throw 400;
            }
            FlightModel flight(0, 0, 0, dispatcherId, planeId, airportId);
            FlightModel created = serv.createFlight(flight, header);
            json flight_json;
            flight_json["id"] = created.getId();
            flight_json["timestampStart"] = created.getTimestampStart();
            flight_json["timestampEnd"] = created.getTimestampEnd();
            flight_json["dispatcherId"] = created.getDispatcherId();
            flight_json["planeId"] = created.getPlaneId();
            flight_json["airportId"] = created.getAirportId();
            res.status = 200;
            res.set_content(flight_json.dump(), "application/json");
        } catch (int& e)
        {
            res.status = e;
        } catch (const exception& e)
        {
            string str(e.what());
            res.status = 500;
        } catch (...)
        {
            res.status = 500;
        }
    });
}