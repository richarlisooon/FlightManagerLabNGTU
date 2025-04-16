#include "../../header/models/PlaneModelResponse.h"

PlaneModelResponse::PlaneModelResponse(int id, std::string name, std::string pilot, int builtYear, int brokenPercentage, int speed, int minAirportSize, double x, double y)
{
    _id = id;
    _name = name;
    _pilot = pilot;
    _builtYear = builtYear;
    _brokenPercentage = brokenPercentage;
    _speed = speed;
    _minAirportSize = minAirportSize;
    _x = x;
    _y = y;
}

long int PlaneModelResponse::getId()
{
    return _id;
}
std::string PlaneModelResponse::getName()
{
    return _name;
}
std::string PlaneModelResponse::getPilot()
{
    return _pilot;
}
int PlaneModelResponse::getSpeed()
{
    return _speed;
}
int PlaneModelResponse::getBrokenPercentage()
{
    return _brokenPercentage;
}
int PlaneModelResponse::getBuiltYear()
{
    return _builtYear;
}
int PlaneModelResponse::getMinAirportSize()
{
    return _minAirportSize;
}
double PlaneModelResponse::getX()
{
    return _x;
}
double PlaneModelResponse::getY()
{
    return _y;
}

void PlaneModelResponse::setId(long int id)
{
    _id = id;
}
void PlaneModelResponse::setName(std::string name)
{
    _name = name;
}
void PlaneModelResponse::setPilot(std::string pilot)
{
    _pilot = pilot;
}
void PlaneModelResponse::setBrokenPercentage(int brokenPercentage)
{
    _brokenPercentage = brokenPercentage;
}
void PlaneModelResponse::setBuiltYear(int builtYear)
{
    _builtYear = builtYear;
}
void PlaneModelResponse::setSpeed(int speed)
{
    _speed = speed;
}
void PlaneModelResponse::setMinAirportSize(int minAirportSize)
{
    _minAirportSize = minAirportSize;
}
void PlaneModelResponse::setX(double x)
{
    _x = x;
}
void PlaneModelResponse::setY(double y)
{
    _y = y;
}
