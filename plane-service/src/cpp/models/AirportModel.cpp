#include "../../header/models/AirportModel.h"
AirportModel::AirportModel(long int id, std::string name, int size, double x, double y)
{
    _id = id;
    _name = name;
    _size = size;
    _x = x;
    _y = y;
}

long int AirportModel::getId()
{
    return _id;
}
std::string AirportModel::getName()
{
    return _name;
}
int AirportModel::getSize()
{
    return _size;
}
double AirportModel::getX()
{
    return _x;
}
double AirportModel::getY()
{
    return _y;
}

void AirportModel::setId(long int id)
{
    _id = id;
}
void AirportModel::setName(std::string name)
{
    _name = name;
}
void AirportModel::setSize(int size)
{
    _size = size;
}
void AirportModel::setX(double x)
{
    _x = x;
}
void AirportModel::setY(double y)
{
    _y = y;
}

