#pragma once
#include <string>
namespace src
{
    // gateway connection
    const std::string GATEWAY_URL = std::string(std::getenv("GATEWAY_URL"));
    const std::string GATEWAY_HOST_PORT = GATEWAY_URL.substr(GATEWAY_URL.find("://") + 3, GATEWAY_URL.length() - GATEWAY_URL.find("://") - 4);
    const std::string AUTH_TOKEN_NAME = "Authorization";

    //mappings
    const std::string LOGIN_MAPPING = "/api/auth/login";
    const std::string REGISTER_MAPPING = "/api/auth/register";

    const std::string AIRPORT_GET_ALL_MAPPING = "/api/airport/getAll";
    const std::string AIRPORT_CREATE_MAPPING = "/api/airport/create";
    const std::string AIRPORT_UPDATE_MAPPING = "/api/airport/update";
    const std::string AIRPORT_DELETE_MAPPING = "/api/airport/delete";


    const std::string PLANE_GET_ALL_MAPPING = "/api/plane/getAll";
    const std::string PLANE_CREATE_MAPPING = "/api/plane/create";
    const std::string PLANE_UPDATE_MAPPING = "/api/plane/update";
    const std::string PLANE_DELETE_MAPPING = "/api/plane/delete";

    const std::string DISPATCHER_GET_ALL_MAPPING = "/api/dispatcher/getAll";
    const std::string DISPATCHER_GET_BY_ID_MAPPING = "/api/dispatcher/get";
    const std::string DISPATCHER_UPDATE_MAPPING = "/api/dispatcher/update";

    const std::string FLIGHT_GET_ALL_MAPPING = "/api/flights/getAll";
    const std::string FLIGHT_CREATE_MAPPING = "/api/flights/create";

    const std::string TIME_SKIP_MAPPING = "/api/time/skip";
    const std::string TIME_GET_MAPPING = "/api/time/get";


    const std::string TOKEN_FILE_PATH = std::string(std::getenv("CLIENT_CREDENTIALS_PATH"));
    const std::string LOGS_FILE_PATH = std::string(std::getenv("LOGS_FILE_PATH"));

    const bool LOGS_ENABLED = std::string(std::getenv("LOGS_ENABLED")) == "true";
    const bool LOGGER_FILE = std::string(std::getenv("LOGGER_FILE")) == "true";
    const bool LOGGER_CONSOLE = std::string(std::getenv("LOGGER_CONSOLE")) == "true";
}