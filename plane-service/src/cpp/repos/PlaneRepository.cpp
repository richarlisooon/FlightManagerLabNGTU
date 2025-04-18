#include "../../header/repos/PlaneRepository.h"
#include "../../Config.h"
#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>

using namespace std;
using namespace httplib;
using namespace nlohmann;
list<PlaneModel> PlaneRepository::getPlanes(long int* id, string* name, string* pilot, int* builtYear, int* brokenPercentage, int* speed, int* minAirportSize)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    Params params;
    if (id != nullptr)
        params.insert(make_pair("id", to_string(*id)));
    if (name != nullptr)
        params.insert(make_pair("name", *name));
    if (pilot != nullptr)
        params.insert(make_pair("pilot", *pilot));
    if (builtYear != nullptr)
        params.insert(make_pair("builtYear", to_string(*builtYear)));
    if (brokenPercentage != nullptr)
        params.insert(make_pair("brokenPercentage", to_string(*brokenPercentage)));
    if (speed != nullptr)
        params.insert(make_pair("speed", to_string(*speed)));
    if (minAirportSize != nullptr)
        params.insert(make_pair("minAirportSize", to_string(*minAirportSize)));
    auto res = cli.Get(DATABASE_PLANE_GET_MAPPING, params, headers);
    if (res->status >= 200 && res->status < 300)
    {
        json planes = json::parse(res->body);
        list<PlaneModel> result;
        for (auto item: planes)
        {
            PlaneModel plane(item["id"], item["name"],item["pilot"], item["builtYear"], item["brokenPercentage"],item["speed"], item["minAirportSize"]);
            result.push_back(plane);
        }
        return result;
    }
    throw res->status;
}
PlaneModel PlaneRepository::createPlane(PlaneModel plane)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    json plane_json;
    plane_json["id"] = plane.getId();
    plane_json["name"] = plane.getName();
    plane_json["pilot"] = plane.getPilot();
    plane_json["builtYear"] = plane.getBuiltYear();
    plane_json["brokenPercentage"] = plane.getBrokenPercentage();
    plane_json["speed"] = plane.getSpeed();
    plane_json["minAirportSize"] = plane.getMinAirportSize();

    auto res = cli.Post(DATABASE_PLANE_CREATE_MAPPING, headers, plane_json.dump(), "application/json");
    if (res->status >= 200 && res->status < 300)
    {
        json plane_json = json::parse(res->body);
        PlaneModel plane(plane_json["id"], plane_json["name"],plane_json["pilot"], plane_json["builtYear"], plane_json["brokenPercentage"],plane_json["speed"], plane_json["minAirportSize"]);
        return plane;
    }
    throw res->status;
}
bool PlaneRepository::deletePlane(long int id)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };

    auto res = cli.Delete(DATABASE_PLANE_DELETE_MAPPING + "/" + to_string(id), headers);
    if (res->status >= 200 && res->status < 300)
        return true;
    throw res->status;
}
PlaneModel PlaneRepository::updatePlane(PlaneModel plane, set<string> updates)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    json plane_json;
    plane_json["id"] = plane.getId();
    plane_json["name"] = plane.getName();
    plane_json["pilot"] = plane.getPilot();
    plane_json["builtYear"] = plane.getBuiltYear();
    plane_json["brokenPercentage"] = plane.getBrokenPercentage();
    plane_json["speed"] = plane.getSpeed();
    plane_json["minAirportSize"] = plane.getMinAirportSize();
    string update;
    for (auto item: updates)
    {
        if (update.empty())
            update = item;
        else
            update += "," + item;
    }
    auto res = cli.Post(DATABASE_PLANE_UPDATE_MAPPING + "?update=" + update, headers, plane_json.dump(), "application/json");
    if (res->status >= 200 && res->status < 300)
    {
        json plane_json = json::parse(res->body);
        PlaneModel plane(plane_json["id"], plane_json["name"],plane_json["pilot"], plane_json["builtYear"], plane_json["brokenPercentage"],plane_json["speed"], plane_json["minAirportSize"]);
        return plane;
    }
    throw res->status;
}

