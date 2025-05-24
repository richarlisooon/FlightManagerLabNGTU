cmake_minimum_required(VERSION 3.5)
project(client)

add_library(src
        cpp/models/AirportModel.cpp
        cpp/models/DispatcherModel.cpp
        cpp/models/FlightModel.cpp
        cpp/models/PlaneModel.cpp
        cpp/models/PlaneModelResponse.cpp
        cpp/presenter/AirportPresenter.cpp
        cpp/presenter/DispatcherPresenter.cpp
        cpp/presenter/FlightPresenter.cpp
        cpp/presenter/IdentityPresenter.cpp
        cpp/presenter/PlanePresenter.cpp
        cpp/presenter/TimePresenter.cpp
        cpp/repos/AirportRepository.cpp
        cpp/repos/DispatcherRepository.cpp
        cpp/repos/FlightRepository.cpp
        cpp/repos/IdentityRepository.cpp
        cpp/repos/PlaneRepository.cpp
        cpp/repos/TimeRepository.cpp
        cpp/repos/TokenRepository.cpp
        cpp/utils/ClientLogger.cpp
        include/models/AirportModel.h
        include/models/DispatcherModel.h
        include/models/FlightModel.h
        include/models/PlaneModel.h
        include/models/PlaneModelResponse.h
        include/models/RoleModel.h
        include/presentation/AirportPresenter.h
        include/presentation/DispatcherPresenter.h
        include/presentation/FlightPresenter.h
        include/presentation/IdentityPresenter.h
        include/presentation/IPresenter.h
        include/presentation/PlanePresenter.h
        include/presentation/TimePresenter.h
        include/repos/AirportRepository.h
        include/repos/DispatcherRepository.h
        include/repos/FlightRepository.h
        include/repos/IdentityRepository.h
        include/repos/PlaneRepository.h
        include/repos/TimeRepository.h
        include/repos/TokenRepository.h
        include/utils/ClientLogger.h
        include/Config.h
        include/srclib.h
)

target_link_libraries(src nlohmann_json httplib)
if (WIN32)
    target_link_libraries(src wsock32 ws2_32)
endif ()

add_executable(client main.cpp)
target_link_libraries(client src)