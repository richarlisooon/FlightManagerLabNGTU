#pragma once

#include <string>

class PlaneModel
{
private:
    long int _id;
    std::string _name;
    std::string _pilot;
    int _builtYear;
    int _brokenPercentage;
    int _speed;
    int _minAirportSize;
public:
    PlaneModel(long int id, std::string name, std::string pilot, int builtYear, int brokenPercentage, int speed, int minAirportSize);

    long int getId();
    std::string getName();
    std::string getPilot();
    int getBuiltYear();
    int getBrokenPercentage();
    int getSpeed();
    int getMinAirportSize();

    void setId(long int id);
    void setName(std::string name);
    void setPilot(std::string pilot);
    void setBuiltYear(int builtYear);
    void setBrokenPercentage(int brokenPercentage);
    void setSpeed(int speed);
    void setMinAirportSize(int minAirportSize);

};

