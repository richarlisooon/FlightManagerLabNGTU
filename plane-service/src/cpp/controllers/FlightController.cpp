#include "../../header/controllers/FlightController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>



using namespace nlohmann;
using namespace httplib;
using namespace std;


void FlightController::configure(Server* server)
{
    server->Get(FLIGHT_GET_ALL_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE) {
                log.warn("get flights failed: forbidden access [code 403]");
                throw string("403 Forbidden access");
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
            log.info("get flights successful: (" + to_string(flights_json.size()) + " entities) [code 200]");
        } catch (string& e)
        {
            log.warn(e);
            res.status = stoi(e);
            res.set_content(e, "text/plain");
        } catch (const exception& e)
        {
            string str(e.what());
            log.warn("get flights failed: " + str + " [code 500]");
            res.status = 500;
            res.set_content(e.what(), "text/plain");
        } catch (...)
        {
            log.error("unknown error occured");
            res.status = 500;
            res.set_content("unknown error occured", "text/plain");
        }
    });
    server->Post(FLIGHT_CREATE_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE) {
                log.warn("create flight failed: forbidden access [code 403]");
                throw string("403 Forbidden access");
            }
            json request;
            try
            {
                request = json::parse(req.body);
            } catch (...)
            {
                log.warn("create flight failed: invalid data [code 400]");
                throw string("400 Bad request");
            }
            long int dispatcherId, planeId, airportId;
            try
            {
                dispatcherId = request["dispatcherId"];
                planeId = request["planeId"];
                airportId = request["airportId"];
            } catch (...)
            {
                log.warn("create flight failed: invalid data [code 400]");
                throw string("400 Invalid data");
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
            log.info("create flight successful: id=" + to_string(flight_json["id"]) + " [code[200]");
        } catch (string& e)
        {
            log.warn(e);
            res.status = stoi(e);
            res.set_content(e, "text/plain");
        } catch (const exception& e)
        {
            string str(e.what());
            log.warn("create flight failed: " + str + " [code 500]");
            res.status = 500;
            res.set_content(e.what(), "text/plain");
        } catch (...)
        {
            log.error("unknown error occured");
            res.status = 500;
            res.set_content("unknown error occured", "text/plain");
        }
    });
}