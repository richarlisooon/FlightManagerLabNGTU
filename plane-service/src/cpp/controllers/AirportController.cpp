#include "../../header/controllers/AirportController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>
#include <string>
#include <sstream>

using namespace nlohmann;
using namespace httplib;
using namespace std;

void AirportController::configure(Server* server)
{
    // sample request handlers
    server->Get(AIRPORT_GET_ALL_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE) {
                log.warn("get airports failed: forbidden access [code 403]");
                throw string("403 Forbidden access");
            }
            list<AirportModel> airports = serv.getAllAirports(header);
            json airports_json = json::array();
            for (auto airport : airports) {
                json airport_json;
                airport_json["id"] = airport.getId();
                airport_json["name"] = airport.getName();
                airport_json["size"] = airport.getSize();
                airport_json["x"] = airport.getX();
                airport_json["y"] = airport.getY();
                airports_json.push_back(airport_json);
            }
            res.status = 200;
            res.set_content(airports_json.dump(), "application/json");
            log.info("get airports successful (" + to_string(airports_json.size()) + " entities) [code 200]");
        } catch (string& e)
        {
            log.warn(e);
            res.status = stoi(e);
            res.set_content(e, "text/plain");
        } catch (const exception& e)
        {
            string str(e.what());
            log.warn("get airports failed: " + str + " [code 500]");
            res.status = 500;
            res.set_content(e.what(), "text/plain");
        } catch (...)
        {
            log.error("unknown error occured");
            res.status = 500;
            res.set_content("unknown error occured", "text/plain");
        }
    });

    server->Post(AIRPORT_CREATE_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE) {
                log.warn("create airport failed: forbidden access [code 403]");
                throw string("403 Forbidden access");
            }
            json request;
            try
            {
                request = json::parse(req.body);
            } catch (...)
            {
                log.warn("create airport failed: invalid data [code 400]");
                throw string("400 Bad request");
            }
            string name;
            int size;
            double x,y;
            try
            {
                name = request["name"];
                size = request["size"];
                x = request["x"];
                y = request["y"];
            } catch (...)
            {
                log.warn("create airport failed: invalid data [code 400]");
                throw string("400 Invalid data");
            }
            AirportModel created = serv.createAirport(AirportModel(0, name, size, x, y), header);
            json airport_json;
            airport_json["id"] = created.getId();
            airport_json["name"] = created.getName();
            airport_json["size"] = created.getSize();
            airport_json["x"] = created.getX();
            airport_json["y"] = created.getY();
            res.status = 201;
            res.set_content(airport_json.dump(), "application/json");
            log.info("create airport successful: id=" + to_string(airport_json["id"]) + " [code 200]");
        }  catch (string& e)
        {
            log.warn(e);
            res.status = stoi(e);
            res.set_content(e, "text/plain");
        }catch (const exception& e)
        {
            string str(e.what());
            log.warn("create airport failed: " + str + " [code 500]");
            res.status = 500;
            res.set_content(e.what(), "text/plain");
        } catch (...)
        {
            log.error("unknown error occured");
            res.status = 500;
            res.set_content("unknown error occured", "text/plain");
        }
    });

    server->Post(AIRPORT_UPDATE_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string fields;
            try
            {
                fields = req.get_param_value("update");
            } catch (...)
            {
                log.warn("update failed: invalid parameter 'update' [code 400]");
                throw string("400 Invalid update fields");
            }
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE) {
                log.warn("update airport failed: forbidden access [code 403]");
                throw string("403 Forbidden access");
            }
            stringstream ss(fields);
            string item;
            set<string> updates;
            while (getline(ss, item, ','))
            {
                item.erase(0, item.find_first_not_of(" \n\r\t"));
                item.erase(item.find_last_not_of(" \n\r\t") + 1);
                if (!item.empty())
                    updates.insert(item);
            }
            json request;
            try
            {
                request = json::parse(req.body);
            } catch (...)
            {
                log.warn("update airport failed: invalid data [code 400]");
                throw string("400 Bad request");
            }
            for (auto update : updates)
            {
                if (request[update].is_null())
                {
                    log.warn("update airport failed: fields to update not provided [code 400]");
                    throw string("400 Fields to update not provided");
                }
                if (request["id"].is_null())
                {
                    log.warn("update airport failed: id not provided [code 400]");
                    throw string("400 Id not provided");
                }

            }
            string name;
            int size;
            double x, y;
            try
            {
                if (!request["name"].is_null()) name = request["name"]; else  name = "string";
                if (!request["size"].is_null()) size = request["size"]; else size = 0;
                if (!request["x"].is_null()) x = request["x"]; else x = 0;
                if (!request["y"].is_null()) y = request["y"]; else y = 0;
            } catch (...)
            {
                log.warn("update airport failed: invalid data [code 400]");
                throw string("400 Invalid data");
            }
            AirportModel airport(request["id"], name, size, x, y);
            AirportModel updated = serv.updateAirport(airport, updates, header);
            updates.clear();
            json airport_json;
            airport_json["id"] = updated.getId();
            airport_json["name"] = updated.getName();
            airport_json["size"] = updated.getSize();
            airport_json["x"] = updated.getX();
            airport_json["y"] = updated.getY();
            res.status = 201;
            res.set_content(airport_json.dump(), "application/json");
            log.info("update airport successful: id=" + to_string(airport_json["id"]) + " [code 200]");
        } catch (string& e)
        {
            log.warn(e);
            res.status = stoi(e);
            res.set_content(e, "text/plain");
        } catch (const exception& e)
        {
            string str(e.what());
            log.warn("update airport failed: " + str + " [code 500]");
            res.status = 500;
            res.set_content(e.what(), "text/plain");
        } catch (...)
        {
            log.error("unknown error occured");
            res.status = 500;
            res.set_content("unknown error occured", "text/plain");
        }
    });

    server->Delete(AIRPORT_DELETE_MAPPING, [this](const Request& req, Response& res)
{
    try
    {
        auto header = req.get_header_value("Authorization");
        string service_token = req.get_header_value("Service-Token");
        if (service_token != SERVICE_TOKEN_VALUE) {
            log.warn("update airport failed: forbidden access [code 403]");
            throw string("403 Forbidden access");
        }
        long int id;
        try
        {
            id = stol(req.get_param_value("id"));
        } catch (...)
        {
            log.warn("update airport failed: invalid data [code 400]");
            throw string("400 Invalid parameter id");
        }
        serv.deleteAirport(id, header);
        res.status = 200;
        log.info("airport delete successful: id=" + to_string(id) + " [code 200]");
    }  catch (string& e)
    {
        log.warn(e);
        res.status = stoi(e);
        res.set_content(e, "text/plain");
    } catch (const exception& e)
    {
        string str(e.what());
        log.warn("get airport failed: " + str + " [code 500]");
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

