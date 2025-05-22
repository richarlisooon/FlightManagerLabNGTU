#pragma once

#include <list>
#include <set>
#include "../models/PlaneModel.h"
#include "../models/PlaneModelResponse.h"

namespace src
{
    class PlaneRepository
    {
    public:
        std::list<PlaneModelResponse> getPlanes(std::string token);
        PlaneModel createPlane(PlaneModel plane, std::string token);
        bool deletePlane(long int id, std::string token);
        PlaneModel updatePlane(PlaneModel plane, std::set<std::string> update, std::string token);


    };
}