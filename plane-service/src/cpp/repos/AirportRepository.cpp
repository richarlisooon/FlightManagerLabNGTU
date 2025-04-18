#include "../../header/repos/AirportRepository.h"
#include "../../Config.h"
#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;
using namespace httplib;
list<AirportModel> AirportRepository::getAirports(long int* id, string* name, int* size, double* x, double* y)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);

    Headers headers = {
        {SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE}
    };
    Params params;
    if (id != nullptr)
        params.insert({"id", to_string(*id)});
    if (name != nullptr)
        params.insert({"name", *name});
    if (size != nullptr)
        params.insert({"size", to_string(*size)});
    if (x != nullptr)
        params.insert({"x", to_string(*x)});
    if (y != nullptr)
        params.insert({"y", to_string(*y)});
    auto res = cli.Get(DATABASE_AIRPORT_GET_MAPPING, params, headers);
    if (res->status >= 200 && res->status < 300)
    {
        json airports = json::parse(res->body);
        list<AirportModel> result;
        for (auto item : airports)
        {
            AirportModel airport(item["id"], item["name"], item["size"], item["x"], item["y"]);
            result.push_back(airport);
        }
        return result;
    }
    throw res->status;
}
AirportModel AirportRepository::createAirport(AirportModel airport)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);

    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    json airport_json;
    airport_json["id"] = airport.getId();
    airport_json["name"] = airport.getName();
    airport_json["size"] = airport.getSize();
    airport_json["x"] = airport.getX();
    airport_json["y"] = airport.getY();

    auto res = cli.Post(DATABASE_AIRPORT_CREATE_MAPPING, headers, airport_json.dump(), "application/json");
    if (res->status >= 200 && res->status < 300)
    {
        json airport_json = json::parse(res->body);
        AirportModel airport(airport_json["id"], airport_json["name"], airport_json["size"], airport_json["x"], airport_json["y"]);
        return airport;
    }

    throw res->status;
}
AirportModel AirportRepository::updateAirport(AirportModel airport, set<string> updates)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);
    Headers headers = {
        { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
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
    auto res = cli.Post((DATABASE_AIRPORT_UPDATE_MAPPING + "?update=" + update), headers, airport_json.dump(), "application/json");
    if (res->status >= 200 && res->status < 300)
    {
        json airport_json = json::parse(res->body);
        AirportModel airport(airport_json["id"], airport_json["name"], airport_json["size"], airport_json["x"], airport_json["y"]);
        return airport;
    }
    throw res->status;
}


bool AirportRepository::deleteAirport(long int id)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);

    Headers headers = {
    { SERVICE_TOKEN_NAME, SERVICE_TOKEN_VALUE }
    };
    auto res = cli.Delete(DATABASE_AIRPORT_DELETE_MAPPING + "/" + to_string(id), headers);
    if (res->status >= 200 && res->status < 300)
        return true;
    throw res->status;
}