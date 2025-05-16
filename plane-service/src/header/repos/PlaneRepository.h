#pragma once
#include <list>
#include <set>
#include <string>
#include "../models/PlaneModel.h"

class PlaneRepository
{
public:
    std::list<PlaneModel> getPlanes(long int* id = nullptr, std::string* name = nullptr, std::string* pilot = nullptr, int* builtYear = nullptr, int* brokenPercentage = nullptr, int* speed = nullptr, int* minAirportSize = nullptr);
    PlaneModel createPlane(PlaneModel plane);
    bool deletePlane(long int id);
    PlaneModel updatePlane(PlaneModel plane, std::set<std::string> update);


};