#include "../../include/repos/AirportRepository.h"
#include "../../include/Config.h"

#include <httplib.h>
#include <nlohmann/json.hpp>

using namespace std;
using namespace src;
using namespace httplib;
using namespace nlohmann;

list<AirportModel> AirportRepository::getAllAirports(string token)
{
    Client cli(GATEWAY_HOST_PORT);

    Headers headers = {
        {AUTH_TOKEN_NAME, token}
    };
    Params params;
    auto res = cli.Get("/api/airport/getAll", params, headers);
    if (res->status >= 200 && res->status < 300)
    {
        json airports = json::parse(res->body);
        list<AirportModel> result;
        for (auto& item : airports)
        {
            AirportModel airport(item["id"], item["name"], item["size"], item["x"], item["y"]);
            result.push_back(airport);
        }
        return result;
    }
    throw res->status;
}

AirportModel AirportRepository::createAirport(AirportModel airport, string token)
{
    Client cli(GATEWAY_HOST_PORT);

    Headers headers = {
        {AUTH_TOKEN_NAME, token}
    };
    json airport_json;
    airport_json["name"] = airport.getName();
    airport_json["size"] = airport.getSize();
    airport_json["x"] = airport.getX();
    airport_json["y"] = airport.getY();

    auto res = cli.Post(AIRPORT_CREATE_MAPPING, headers, airport_json.dump(), "application/json");
    if (res->status >= 200 && res->status < 300)
    {
        json airports = json::parse(res->body);
        AirportModel airport(airports["id"], airports["name"], airports["size"], airports["x"], airports["y"]);
        return airport;
    }
    throw res->status;
}

bool AirportRepository::deleteAirport(long int id, string token)
{
    Client cli(GATEWAY_HOST_PORT);

    Headers headers = {
        {AUTH_TOKEN_NAME, token}
    };
    auto res = cli.Delete(AIRPORT_DELETE_MAPPING + "?id=" + to_string(id), headers);
    if (res->status >= 200 && res->status < 300)
        return true;
    throw res->status;
}

AirportModel AirportRepository::updateAirport(AirportModel airport, set<string> updates, string token)
{
    Client cli(GATEWAY_HOST_PORT);
    Headers headers = {
        {AUTH_TOKEN_NAME, token}
    };

    json airport_json;
    airport_json["id"] = airport.getId();
    airport_json["name"] = airport.getName();
    airport_json["size"] = airport.getSize();
    airport_json["x"] = airport.getX();
    airport_json["y"] = airport.getY();
    string update;
    for (auto item : updates)
    {
        if (update.empty())
            update = item;
        else
            update += "," + item;
    }
    auto res = cli.Post((AIRPORT_UPDATE_MAPPING + "?update=" + update), headers, airport_json.dump(),
                        "application/json");
    if (res->status >= 200 && res->status < 300)
    {
        json airports = json::parse(res->body);
        AirportModel airport(airports["id"], airports["name"], airports["size"], airports["x"], airports["y"]);
        return airport;
    }
    throw res->status;
}
