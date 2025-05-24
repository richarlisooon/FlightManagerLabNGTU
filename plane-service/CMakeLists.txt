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
        src/cpp/repos/TimeRepository.cpp
        src/header/services/AirportService.h
        src/header/services/DispatcherService.h
        src/header/services/PlaneService.h
        src/header/services/FlightService.h
        src/header/services/TimeService.h
        src/cpp/services/AirportService.cpp
        src/cpp/services/DispatcherService.cpp
        src/cpp/services/PlaneService.cpp
        src/cpp/services/FlightService.cpp
        src/cpp/services/TimeService.cpp
        src/header/controllers/AirportController.h
        src/header/controllers/Config.h
        src/header/controllers/DispatcherController.h
        src/header/controllers/FlightController.h
        src/header/controllers/IController.h
        src/header/controllers/PlaneController.h
        src/header/controllers/TimeController.h
        src/cpp/controllers/AirportController.cpp
        src/cpp/controllers/DispatcherController.cpp
        src/cpp/controllers/FlightController.cpp
        src/cpp/controllers/PlaneController.cpp
        src/cpp/controllers/TimeController.cpp
        src/cpp/utils/PlaneLogger.cpp
        src/header/utils/PlaneLogger.h
        src/Config.h)

