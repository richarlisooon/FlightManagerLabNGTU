#include "../../include/presentation/TimePresenter.h"
#include "../../include/repos/TimeRepository.h"
#include "../../include/repos/TokenRepository.h"

using namespace src;
using namespace std;

void TimePresenter::getCurrentTime()
{
    try
    {
        TimeRepository timeRepo;
        string token = TokenRepository().getToken(); // Получаем токен авторизации
        string currentTime = timeRepo.getCurrentTime(token);
        log.info("time get successful: [code 200]");
        *_output << "Current Time: " << currentTime << endl;
    }
    catch (const int& status) {
        *_output << "Error getting time. Status: " << status << endl;
        if (status == 500) {
            log.warn("time get failed: internal server error [code 500]");
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            log.warn("time get failed: bad request [code 400]");
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 403) {
            log.warn("time get failed: forbidden access [code 403]");
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 401) {
            log.warn("time get failed: unauthorized access [code 401]");
            *_output << "Unauthorized access. Please log in." << endl;
        }
    } catch (...) {
        log.error("unknown error");
        *_output << "Unknown error. Call to support" << endl;
    }
}

void TimePresenter::addTime()
{
    try
    {
        long int timeToAdd;
        try
        {
            string timeToAdd1;
            *_output << "Enter time to add (in seconds): ";
            *_input >> timeToAdd1;
            timeToAdd = stol(timeToAdd1);
        }
        catch (...)
        {
            throw 400;
        }


        TimeRepository timeRepo;
        string token = TokenRepository().getToken(); // Получаем токен авторизации


        timeRepo.addTime(timeToAdd, token);
        log.info("time add successful: skip=" + to_string(timeToAdd) + " [code 200]");
        *_output << "Time added successfully!" << endl;
    }
    catch (const int& status) {
        *_output << "Error adding time. Status: " << status << endl;
        if (status == 500) {
            log.warn("time add failed: internal server error [code 500]");
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            log.warn("time add failed: bad request [code 400]");
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 403) {
            log.warn("time add failed: forbidden access [code 403]");
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 401) {
            log.warn("time add failed: unauthorized access [code 401]");
            *_output << "Unauthorized access. Please log in." << endl;
        }
    } catch (...) {
        log.error("unknown error");
        *_output << "Unknown error. Call to support" << endl;
    }
}
