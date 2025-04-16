#include "../../header/models/PlaneModel.h"
PlaneModel::PlaneModel(long int id, std::string name, std::string pilot, int builtYear, int brokenPercentage, int speed, int minAirportSize)
{
    _id = id;
    _name = name;
    _pilot = pilot;
    _builtYear = builtYear;
    _brokenPercentage = brokenPercentage;
    _speed = speed;
    _minAirportSize = minAirportSize;
}

long int PlaneModel::getId()
{
    return _id;
}
std::string PlaneModel::getName()
{
    return _name;
}
std::string PlaneModel::getPilot()
{
    return _pilot;
}
int PlaneModel::getSpeed()
{
    return _speed;
}
int PlaneModel::getBrokenPercentage()
{
    return _brokenPercentage;
}
int PlaneModel::getBuiltYear()
{
    return _builtYear;
}
int PlaneModel::getMinAirportSize()
{
    return _minAirportSize;
}

void PlaneModel::setId(long int id)
{
    _id = id;
}
void PlaneModel::setName(std::string name)
{
    _name = name;
}
void PlaneModel::setPilot(std::string pilot)
{
    _pilot = pilot;
}
void PlaneModel::setBrokenPercentage(int brokenPercentage)
{
    _brokenPercentage = brokenPercentage;
}
void PlaneModel::setBuiltYear(int builtYear)
{
    _builtYear = builtYear;
}
void PlaneModel::setSpeed(int speed)
{
    _speed = speed;
}
void PlaneModel::setMinAirportSize(int minAirportSize)
{
    _minAirportSize = minAirportSize;
}







