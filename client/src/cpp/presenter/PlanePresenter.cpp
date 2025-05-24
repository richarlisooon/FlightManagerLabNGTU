#include "../../include/presentation/PlanePresenter.h"
#include "../../include/repos/PlaneRepository.h"
#include "../../include/repos/TokenRepository.h"
#include <iomanip>

using namespace src;
using namespace std;

void PlanePresenter::getPlanes()
{
    PlaneRepository planeRepo;
    string token = TokenRepository().getToken(); // Получаем токен авторизации

    try
    {
        list<PlaneModelResponse> planes = planeRepo.getPlanes(token);
        log.info("planes get successful: (" + to_string(planes.size()) + " entities) [code 200]");
        if (planes.empty())
        {
            *_output << "No planes found." << endl;
            return;
        }
        *_output << "Planes: " << endl;
        *_output << setw(10) << "ID"
            << setw(10) << "Name"
            << setw(10) << "Pilot"
            << setw(20) << "Built Year"
            << setw(20) << "Broken Percentage"
            << setw(10) << "Speed"
            << setw(25) << "Min Airport Size"
            << setw(10) << "Coordinates" << endl;

        for (auto& plane : planes)
        {
            *_output << setw(10) << plane.getId()
                << setw(10) << plane.getName()
                << setw(10) << plane.getPilot()
                << setw(20) << plane.getBuiltYear()
                << setw(20) << plane.getBrokenPercentage()
                << setw(10) << plane.getSpeed()
                << setw(25) << plane.getMinAirportSize()
                << setw(10) << "(" << plane.getX() << "," << plane.getY() << ")" << endl;
        }
    }
    catch (const int& status) {
        *_output << "Error getting planes. Status: " << status << endl;
        if (status == 500) {
            log.warn("planes get failed: internal server error [code 500]");
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            log.warn("planes get failed: bad request [code 400]");
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 403) {
            log.warn("planes get failed: forbidden access [code 403]");
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 401) {
            log.warn("planes get failed: unauthorized access [code 401]");
            *_output << "Unauthorized access. Please log in." << endl;
        }
    } catch (...) {
        log.error("unknown error");
        *_output << "Unknown error. Call to support" << endl;
    }
}

void PlanePresenter::createPlane()
{
    try
    {
        string name, pilot;
        int builtYear, speed, minAirportSize;
        try
        {
            *_output << "Enter plane name: ";
            *_input >> name;

            *_output << "Enter pilot name: ";
            *_input >> pilot;

            string builtYear1, speed1, minAirportSize1;
            *_output << "Enter built year: ";
            *_input >> builtYear1;
            builtYear = stoi(builtYear1);

            *_output << "Enter speed: ";
            *_input >> speed1;
            speed = stoi(speed1);

            *_output << "Enter minimum airport size: ";
            *_input >> minAirportSize1;
            minAirportSize = stoi(minAirportSize1);
        }
        catch (...)
        {
            throw 400;
        }
        PlaneModel newPlane(0, name, pilot, builtYear, 0, speed, minAirportSize);
        PlaneRepository planeRepo;
        string token = TokenRepository().getToken(); // Получаем токен авторизации

        // Отправляем новый объект самолета на сервер и получаем результат
        PlaneModel result = planeRepo.createPlane(newPlane, token);
        log.info("plane create successful: id=" + to_string(result.getId()) + " [code 200]");
        // Проверяем, был ли самолет успешно создан, например, по ID или другим критериям
        *_output << "Plane created successfully!" << endl;
        *_output << setw(10) << "ID"
            << setw(10) << "Name"
            << setw(10) << "Pilot"
            << setw(20) << "Built Year"
            << setw(20) << "Broken Percentage"
            << setw(10) << "Speed"
            << setw(20) << "Min Airport Size" << endl;


        *_output << setw(10) << result.getId()
            << setw(10) << result.getName()
            << setw(10) << result.getPilot()
            << setw(20) << result.getBuiltYear()
            << setw(20) << result.getBrokenPercentage()
            << setw(10) << result.getSpeed()
            << setw(20) << result.getMinAirportSize() << endl;
    }
    catch (const int& status) {
        *_output << "Error creating planes. Status: " << status << endl;
        if (status == 500) {
            log.warn("planes create failed: internal server error [code 500]");
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            log.warn("planes create failed: bad request [code 400]");
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 409) {
            log.warn("planes create failed: conflict [code 409]");
            *_output << "Conflict" << endl;
        } else if (status == 403) {
            log.warn("planes create failed: forbidden access [code 403]");
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 401) {
            log.warn("planes create failed: unauthorized access [code 401]");
            *_output << "Unauthorized access. Please log in." << endl;
        }
    } catch (...) {
        log.error("unknown error");
        *_output << "Unknown error. Call to support" << endl;
    }
}

void PlanePresenter::updatePlane()
{
    try
    {
        long int id;
        string name, pilot;
        int builtYear, speed, minAirportSize;
        set<string> updates;
        try
        {
            string id1, name1, pilot1;
            *_output << "Enter plane ID to update: ";
            *_input >> id1;
            id = stol(id1);

            *_output << "Enter new plane name (leave - to keep current): ";
            *_input >> name1;
            if (name1 != "-")
            {
                name = name1;
                updates.insert("name");
            }
            else
                name = "";
            *_output << "Enter new pilot name (leave - to keep current): ";
            *_input >> pilot1;
            if (pilot1 != "-")
            {
                pilot = pilot1;
                updates.insert("pilot");
            }
            else
                pilot = "";

            *_output << "Enter new built year (leave - to keep current): ";
            string builtYearInput;
            *_input >> builtYearInput;
            if (builtYearInput != "-")
            {
                builtYear = stoi(builtYearInput);
                updates.insert("builtYear");
            }
            else
                builtYear = -1;

            *_output << "Enter new speed (leave - to keep current): ";
            string speedInput;
            *_input >> speedInput;
            if (speedInput != "-")
            {
                speed = stoi(speedInput);
                updates.insert("speed");
            }
            else
                speed = -1;

            *_output << "Enter new minimum airport size (leave blank to keep current): ";
            string minAirportSizeInput;
            *_input >> minAirportSizeInput;
            if (minAirportSizeInput != "-")
            {
                minAirportSize = stoi(minAirportSizeInput);
                updates.insert("minAirportSize");
            }
            else
                minAirportSize = -1;
        }
        catch (...)
        {
            throw 400;
        }
        PlaneModel updatedPlane(id, name, pilot, builtYear, 0, speed, minAirportSize);
        PlaneRepository planeRepo;
        string token = TokenRepository().getToken();
        PlaneModel result = planeRepo.updatePlane(updatedPlane, updates, token);
        log.info("plane update successful: id=" + to_string(result.getId()) + " [code 200]");
        *_output << "Plane updated successfully!" << endl;
        *_output << setw(10) << "ID"
            << setw(10) << "Name"
            << setw(10) << "Pilot"
            << setw(20) << "Built Year"
            << setw(20) << "Broken Percentage"
            << setw(10) << "Speed"
            << setw(20) << "Min Airport Size" << endl;


        *_output << setw(10) << result.getId()
            << setw(10) << result.getName()
            << setw(10) << result.getPilot()
            << setw(20) << result.getBuiltYear()
            << setw(20) << result.getBrokenPercentage()
            << setw(10) << result.getSpeed()
            << setw(20) << result.getMinAirportSize() << endl;
    }
    catch (const int& status) {
        *_output << "Error updating planes. Status: " << status << endl;
        if (status == 500) {
            log.warn("planes update failed: internal server error [code 500]");
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            log.warn("planes update failed: bad request [code 400]");
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 409) {
            log.warn("planes update failed: conflict [code 409]");
            *_output << "Conflict" << endl;
        } else if (status == 403) {
            log.warn("planes update failed: forbidden access [code 403]");
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 401) {
            log.warn("planes update failed: unauthorized access [code 401]");
            *_output << "Unauthorized access. Please log in." << endl;
        }
    } catch (...) {
        log.error("unknown error");
        *_output << "Unknown error. Call to support" << endl;
    }
}

void PlanePresenter::deletePlane()
{
    try
    {
        long int id;
        try
        {
            string id1;
            *_output << "Enter plane ID to delete: ";
            *_input >> id1;
            id = stol(id1);
        }
        catch (...)
        {
            throw 400;
        }

        PlaneRepository planeRepo;
        string token = TokenRepository().getToken(); // Получаем токен авторизации


        planeRepo.deletePlane(id, token);
        log.info("plane delete successful: id=" + to_string(id) + " [code 200]");
        *_output << "Plane deleted successfully!" << endl;
    }
    catch (const int& status) {
        *_output << "Error deleting planes. Status: " << status << endl;
        if (status == 500) {
            log.warn("planes delete failed: internal server error [code 500]");
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            log.warn("planes delete failed: bad request [code 400]");
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 409) {
            log.warn("planes delete failed: conflict [code 409]");
            *_output << "Conflict" << endl;
        } else if (status == 403) {
            log.warn("planes delete failed: forbidden access [code 403]");
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 401) {
            log.warn("planes delete failed: unauthorized access [code 401]");
            *_output << "Unauthorized access. Please log in." << endl;
        }
    } catch (...) {
        log.error("unknown error");
        *_output << "Unknown error. Call to support" << endl;
    }
}
