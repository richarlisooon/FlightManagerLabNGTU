#pragma once
#include <string>

const int SERVER_PORT = std::stoi(std::string(std::getenv("PLANE_SERVICE_PORT")));
const std::string SERVER_HOST = "0.0.0.0";
const std::string SERVICE_TOKEN_NAME = std::string(std::getenv("SERVICE_TOKEN_NAME"));
const std::string SERVICE_TOKEN_VALUE = std::string(std::getenv("SERVICE_TOKEN_VALUE"));
const std::string AUTHORIZATION_HEADER_NAME = std::string(std::getenv("AUTHORIZATION_HEADER_NAME"));


// database-service connection
const std::string DATABASE_SERVICE_URL = std::string(std::getenv("DATABASE_SERVICE_URL"));
const std::string DATABASE_SERVICE_HOST_PORT = DATABASE_SERVICE_URL.substr(DATABASE_SERVICE_URL.find("://") + 3, DATABASE_SERVICE_URL.length() - DATABASE_SERVICE_URL.find("://") - 4);

const std::string DATABASE_AIRPORT_GET_MAPPING = "/api/airport/get";
const std::string DATABASE_AIRPORT_CREATE_MAPPING = "/api/airport/create";
const std::string DATABASE_AIRPORT_UPDATE_MAPPING = "/api/airport/update";
const std::string DATABASE_AIRPORT_DELETE_MAPPING = "/api/airport/delete";


const std::string DATABASE_PLANE_GET_MAPPING = "/api/plane/get";
const std::string DATABASE_PLANE_CREATE_MAPPING = "/api/plane/create";
const std::string DATABASE_PLANE_UPDATE_MAPPING = "/api/plane/update";
const std::string DATABASE_PLANE_DELETE_MAPPING = "/api/plane/delete";

const std::string DATABASE_DISPATCHER_GET_MAPPING = "/api/dispatcher/get";
const std::string DATABASE_DISPATCHER_UPDATE_MAPPING = "/api/dispatcher/update";

const std::string DATABASE_FLIGHT_GET_MAPPING = "/api/flights/get";
const std::string DATABASE_FLIGHT_CREATE_MAPPING = "/api/flights/create";



// identity-service connection

const std::string IDENTITY_SERVICE_URL = std::string(std::getenv("IDENTITY_SERVICE_URL"));
const std::string IDENTITY_SERVICE_HOST_PORT = IDENTITY_SERVICE_URL.substr(IDENTITY_SERVICE_URL.find("://") + 3, IDENTITY_SERVICE_URL.length() - IDENTITY_SERVICE_URL.find("://") - 4);

const std::string IDENTITY_GET_ID_BY_TOKEN_MAPPING = "/api/auth/getIdByToken";
const std::string IDENTITY_AUTHORIZE_MAPPING = "/api/auth/authorize";

// mappings

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

// path to the time file
const std::string TIME_FILE_PATH = std::string(std::getenv("TIME_FILE_PATH"));
const int addingBrokenPercentage = 3600;