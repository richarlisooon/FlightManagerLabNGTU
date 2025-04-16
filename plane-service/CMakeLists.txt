cmake_minimum_required(VERSION 3.5)
project(plain-service)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libs)
execute_process(
        COMMAND git clone "https://github.com/yhirose/cpp-httplib.git" cpp-httplib
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libs)
execute_process(
        COMMAND git clone "https://github.com/nlohmann/json.git" json
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libs)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/libs)

add_executable(main src/main.cpp
        src/header/repos/AirportRepository.h
        src/header/repos/DispatcherRepository.h
        src/header/repos/FlightRepository.h
        src/header/repos/IdentityRepository.h
        src/header/repos/PlaneRepository.h
        src/header/repos/TimeRepository.h
        src/header/models/AirportModel.h
        src/header/models/DispatcherModel.h
        src/header/models/FlightModel.h
        src/header/models/PlaneModel.h
        src/header/models/PlaneModelResponse.h
        src/header/models/RoleModel.h
        src/cpp/models/AirportModel.cpp
        src/cpp/models/DispatcherModel.cpp
        src/cpp/models/FlightModel.cpp
        src/cpp/models/PlaneModel.cpp
        src/cpp/models/PlaneModelResponse.cpp
        src/cpp/repos/AirportRepository.cpp
        src/cpp/repos/DispatcherRepository.cpp
        src/cpp/repos/FlightRepository.cpp
        src/cpp/repos/IdentityRepository.cpp
        src/cpp/repos/PlaneRepository.cpp
        src/cpp/repos/TimeRepository.cpp)

