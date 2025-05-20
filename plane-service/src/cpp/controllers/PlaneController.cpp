#include "../../header/controllers/PlaneController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>

using namespace nlohmann;
using namespace httplib;
using namespace std;

void PlaneController::configure(Server* server)
{
    server->Get(PLANE_GET_ALL_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE) {
                log.warn("get planes failed: forbidden access [code 403]");
                throw 403;
            }
            list<PlaneModelResponse> planes = serv.getAllPlanes(header);
            json planes_json = json::array();
            for (auto plane : planes)
            {
                json plane_json;
                plane_json["id"] = plane.getId();
                plane_json["name"] = plane.getName();
                plane_json["pilot"] = plane.getPilot();
                plane_json["builtYear"] = plane.getBuiltYear();
                plane_json["brokenPercentage"] = plane.getBrokenPercentage();
                plane_json["speed"] = plane.getSpeed();
                plane_json["minAirportSize"] = plane.getMinAirportSize();
                plane_json["x"] = plane.getX();
                plane_json["y"] = plane.getY();
                planes_json.push_back(plane_json);
            }
            res.status = 200;
            res.set_content(planes_json.dump(), "application/json");
            log.info("get plane successful: (" + to_string(planes_json.size()) + " entities) [code 200]");
        } catch (int& e)
        {
            log.warn("update plane failed: [code " + to_string(e) + "]");
            res.status = e;
        } catch (const exception& e)
        {
            string str(e.what());
            log.warn("get planes failed: " + str + " [code 500]");
            res.status = 500;
        } catch (...)
        {
            log.error("unknown error occured");
            res.status = 500;
        }
    });

    server->Post(PLANE_CREATE_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE) {
                log.warn("get planes failed: forbidden access [code 403]");
                throw 403;
            }
            json request;
            try
            {
                request = json::parse(req.body);
            } catch (...)
            {
                log.warn("create plane failed: inalid data [code 400]");
                throw 400;
            }
            string name, pilot;
            int builtYear, speed, minAirportSize;
            try
            {
                name = request["name"];
                pilot = request["pilot"];
                builtYear = request["builtYear"];
                speed = request["speed"];
                minAirportSize = request["minAirportSize"];
            } catch (...)
            {
                log.warn("create plane failed: inalid data [code 400]");
                throw 400;
            }
            PlaneModel plane(0, name, pilot, builtYear, 0, speed, minAirportSize);
            PlaneModel created = serv.createPlane(plane, header);
            json plane_json;
            plane_json["id"] = created.getId();
            plane_json["name"] = created.getName();
            plane_json["pilot"] = created.getPilot();
            plane_json["builtYear"] = created.getBuiltYear();
            plane_json["brokenPercentage"] = created.getBrokenPercentage();
            plane_json["speed"] = created.getSpeed();
            plane_json["minAirportSize"] = created.getMinAirportSize();
            res.status = 200;
            res.set_content(plane_json.dump(), "application/json");
            log.info("create plane successful: id=" + to_string(plane_json["id"]) + " [code 200]");
        } catch (int& e)
        {
            log.warn("update plane failed: [code " + to_string(e) + "]");
            res.status = e;
        } catch (const exception& e)
        {
            string str(e.what());
            log.warn("create plane failed: " + str + " [code 500]");
            res.status = 500;
        } catch (...)
        {
            log.error("unknown error occured");
            res.status = 500;
        }
    });
    server->Post(PLANE_UPDATE_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE) {
                log.warn("update plane failed: forbidden access [code 403]");
                throw 403;
            }
            string fields;
            try
            {
                fields = req.get_param_value("update");
            } catch (...)
            {
                log.warn("update plane failed: invalid parameter 'update' [code 400]");
                throw 400;
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
                log.warn("update plane failed: invalid data [code 400]");
                throw 400;
            }
            for (auto update : updates)
            {
                if (request[update].is_null())
                {
                    log.warn("update plane failed: fields to update not provided [code 400]");
                    throw 400;
                }
                if (request["id"].is_null())
                {
                    log.warn("update plane failed: id not provided [code 400]");
                    throw 400;
                }

            }
            string name, pilot;
            int builtYear, speed, minAirportSize;
            try
            {
                if (!request["name"].is_null()) name = request["name"]; else name = "string";
                if (!request["pilot"].is_null()) pilot = request["pilot"]; else pilot = "string";
                if (!request["builtYear"].is_null()) builtYear = request["builtYear"]; else builtYear = 0;
                if (!request["speed"].is_null()) speed = request["speed"]; else speed = 0;
                if (!request["minAirportSize"].is_null()) minAirportSize = request["minAirportSize"]; else minAirportSize = 0;
            } catch (...)
            {
                log.warn("update plane failed: fields to update not provided [code 400]");
                throw 400;
            }
            PlaneModel plane(request["id"], name, pilot, builtYear, 0, speed, minAirportSize);
            PlaneModel updated = serv.updatePlane(plane, updates, header);
            updates.clear();
            json plane_json;
            plane_json["id"] = updated.getId();
            plane_json["name"] = updated.getName();
            plane_json["pilot"] = updated.getPilot();
            plane_json["builtYear"] = updated.getBuiltYear();
            plane_json["brokenPercentage"] = updated.getBrokenPercentage();
            plane_json["speed"] = updated.getSpeed();
            plane_json["minAirportSize"] = updated.getMinAirportSize();
            res.status = 200;
            res.set_content(plane_json.dump(), "application/json");
            log.info("update plane successful: id=" + to_string(updated.getId()) + " [code 200]");
        } catch (int& e)
        {
            log.warn("update plane failed: [code " + to_string(e) + "]");
            res.status = e;
        } catch (const exception& e)
        {
            string str(e.what());
            log.warn("update plane failed: " + str + " [code 500]");
            res.status = 500;
        } catch (...)
        {
            log.error("unknown error occured");
            res.status = 500;
        }
    });
    server->Delete(PLANE_DELETE_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE) {
                log.warn("delete plane failed: forbidden access [code 403]");
                throw 403;
            }
            long int id;
            try
            {
                id = stol(req.get_param_value("id"));
            } catch (...)
            {
                log.warn("delete plane failed: invalid id [code 400]");
                throw 400;
            }

            serv.deletePlane(id, header);
            res.status = 200;
            log.info("delete plane successful: id=" + to_string(id) + " [code 200]");
        } catch (int& e)
        {
            log.warn("update plane failed: [code " + to_string(e) + "]");
            res.status = e;
        } catch (const exception& e)
        {
            string str(e.what());
            log.warn("delete plane failed: " + str + " [code 500]");
            res.status = 500;
        } catch (...)
        {
            log.error("unknown error occured");
            res.status = 500;
        }
    });
}
