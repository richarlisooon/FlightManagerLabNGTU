#pragma once

#include <string>

class AirportModel
{
    long int _id;
    std::string _name;
    int _size;
    double _x;
    double _y;
public:
    AirportModel(long int id, std::string name, int size, double x, double y);

    long int getId();
    std::string getName();
    int getSize();
    double getX();
    double getY();

    void setId(long int id);
    void setName(std::string name);
    void setSize(int size);
    void setX(double x);
    void setY(double y);

};
