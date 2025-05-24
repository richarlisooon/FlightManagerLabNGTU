cmake_minimum_required(VERSION 3.5)
project(client)
enable_testing()
include(FetchContent)

FetchContent_Declare(httplib SYSTEM GIT_REPOSITORY https://github.com/yhirose/cpp-httplib GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(httplib)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

add_subdirectory(src)
add_subdirectory(test)