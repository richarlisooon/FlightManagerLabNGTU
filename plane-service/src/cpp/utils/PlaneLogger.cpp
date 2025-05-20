#include "../../header/utils/PlaneLogger.h"

#include <iostream>

using namespace std;
void PlaneLogger::info(std::string inf)
{
    cout << "INFO: " + inf << endl;
}

void PlaneLogger::warn(std::string warn)
{
    cout << "WARN: " + warn << endl;
}
void PlaneLogger::error(std::string err)
{
    cout << "ERROR: " + err << endl;
}
void PlaneLogger::debug(std::string debug)
{
    cout << "DEBUG: " + debug << endl;
}