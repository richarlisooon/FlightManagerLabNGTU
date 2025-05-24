#include "../../include/repos/PlaneRepository.h"
#include "../../include/Config.h"

#include <httplib.h>
#include <nlohmann/json.hpp>

using namespace std;
using namespace src;
using namespace httplib;
using namespace nlohmann;

list<PlaneModelResponse> PlaneRepository::getPlanes(string token)
{
    Client cli(GATEWAY_HOST_PORT);

    Headers headers = {
        {AUTH_TOKEN_NAME, token}
    };
    auto res = cli.Get(PLANE_GET_ALL_MAPPING, headers);
    if (res->status >= 200 && res->status < 300)
    {
        json planes = json::parse(res->body);
        list<PlaneModelResponse> result;
        for (auto item : planes)
        {
            PlaneModelResponse plane(item["id"], item["name"], item["pilot"], item["builtYear"],
                                     item["brokenPercentage"], item["speed"], item["minAirportSize"], item["x"],
                                     item["y"]);
            result.push_back(plane);
        }
        return result;
    }
    throw res->status;
}

PlaneModel PlaneRepository::createPlane(PlaneModel plane, string token)
{
    Client cli(GATEWAY_HOST_PORT);

    Headers headers = {
        {AUTH_TOKEN_NAME, token}
    };
    json plane_json;
    plane_json["name"] = plane.getName();
    plane_json["pilot"] = plane.getPilot();
    plane_json["builtYear"] = plane.getBuiltYear();
    plane_json["speed"] = plane.getSpeed();
    plane_json["minAirportSize"] = plane.getMinAirportSize();

    auto res = cli.Post(PLANE_CREATE_MAPPING, headers, plane_json.dump(), "application/json");
    if (res->status >= 200 && res->status < 300)
    {
        json planes = json::parse(res->body);
        PlaneModel n_plane(planes["id"], planes["name"], planes["pilot"], planes["builtYear"],
                           planes["brokenPercentage"], planes["speed"], planes["minAirportSize"]);
        return n_plane;
    }
    throw res->status;
}

bool PlaneRepository::deletePlane(long int id, string token)
{
    Client cli(GATEWAY_HOST_PORT);

    Headers headers = {
        {AUTH_TOKEN_NAME, token}
    };

    auto res = cli.Delete(PLANE_DELETE_MAPPING + "?id=" + to_string(id), headers);
    if (res->status >= 200 && res->status < 300)
        return true;
    throw res->status;
}

PlaneModel PlaneRepository::updatePlane(PlaneModel plane, set<string> updates, string token)
{
    Client cli(GATEWAY_HOST_PORT);

    Headers headers = {
        {AUTH_TOKEN_NAME, token}
    };
    json plane_json;
    plane_json["id"] = plane.getId();
    plane_json["name"] = plane.getName();
    plane_json["pilot"] = plane.getPilot();
    plane_json["builtYear"] = plane.getBuiltYear();
    plane_json["speed"] = plane.getSpeed();
    plane_json["minAirportSize"] = plane.getMinAirportSize();
    string update;
    for (auto item : updates)
    {
        if (update.empty())
            update = item;
        else
            update += "," + item;
    }
    auto res = cli.Post(PLANE_UPDATE_MAPPING + "?update=" + update, headers, plane_json.dump(), "application/json");
    if (res->status >= 200 && res->status < 300)
    {
        json planes = json::parse(res->body);
        PlaneModel n_plane(planes["id"], planes["name"], planes["pilot"], planes["builtYear"],
                           planes["brokenPercentage"], planes["speed"], planes["minAirportSize"]);
        return n_plane;
    }
    throw res->status;
}
