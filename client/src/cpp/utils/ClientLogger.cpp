#include "../../include/utils/ClientLogger.h"
#include "../../include/Config.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace src;
void ClientLogger::info(std::string inf)
{
    if (LOGS_ENABLED && LOGGER_CONSOLE)
        cout << "INFO: " + inf << endl;
    if (LOGS_ENABLED && LOGGER_FILE){
        ofstream file(LOGS_FILE_PATH, ios::app);
        if(!file.is_open())
        {
            cout << "ERROR opening log file " << LOGS_FILE_PATH << endl;
        }
        file << "INFO: " + inf << endl;
        file.close();
    }
    if (!LOGS_ENABLED)
        return;
}

void ClientLogger::warn(std::string warn)
{
    if (LOGS_ENABLED && LOGGER_CONSOLE)
        cout << "WARN: " + warn << endl;
    if (LOGS_ENABLED && LOGGER_FILE){
        ofstream file(LOGS_FILE_PATH, ios::app);
        if(!file.is_open())
        {
            cout << "ERROR opening log file " << LOGS_FILE_PATH << endl;
        }
        file << "WARN: " + warn << endl;
        file.close();
    }
    if (!LOGS_ENABLED)
        return;
}
void ClientLogger::error(std::string err)
{
    if (LOGS_ENABLED && LOGGER_CONSOLE)
        cout << "ERROR: " + err << endl;
    if (LOGS_ENABLED && LOGGER_FILE){
        ofstream file(LOGS_FILE_PATH, ios::app);
        if(!file.is_open())
        {
            cout << "ERROR opening log file " << LOGS_FILE_PATH << endl;
        }
        file << "ERROR: " + err << endl;
        file.close();
    }
    if (!LOGS_ENABLED)
        return;
}
void ClientLogger::debug(std::string debug)
{
    if (LOGS_ENABLED && LOGGER_CONSOLE)
        cout << "DEBUG: " + debug << endl;
    if (LOGS_ENABLED && LOGGER_FILE){
        ofstream file(LOGS_FILE_PATH, ios::app);
        if(!file.is_open())
        {
            cout << "ERROR opening log file " << LOGS_FILE_PATH << endl;
        }
        file << "DEBUG: " + debug << endl;
        file.close();
    }
    if (!LOGS_ENABLED)
        return;
}
