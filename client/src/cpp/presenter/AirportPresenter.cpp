#include "../../include/presentation/AirportPresenter.h"
#include "../../include/repos/AirportRepository.h"
#include "../../include/repos/TokenRepository.h"
#include <iomanip>

using namespace src;
using namespace std;

void AirportPresenter::getAirports() {
    try {
        AirportRepository airportRepo;
        string token = TokenRepository().getToken();

        // Получаем список аэропортов
        list<AirportModel> airports = airportRepo.getAllAirports(token);
        log.info("airport get successful: (" + to_string(airports.size()) + ") entities [code 200]");
        // Проверяем, есть ли аэропорты
        if (airports.empty()) {
            *_output << "No airports found." << endl;
            return;
        }

        // Выводим заголовки таблицы
        *_output << left; // Выравнивание по левому краю
        *_output << setw(10) << "ID"
                 << setw(10) << "Name"
                 << setw(10) << "Size"
                 << setw(10) << "Coordinates" << endl;

        // Выводим информацию о каждом аэропорте
        for (auto airport : airports) {
            *_output << setw(10) << airport.getId()
                     << setw(10) << airport.getName()
                     << setw(10) << airport.getSize()
                     << setw(10) << "(" << airport.getX() << ", " << airport.getY() << ")" << endl;
        }

    } catch (const int& status) {
        *_output << "Error getting airports. Status: " << status << endl;
        if (status == 500) {
            log.warn("airport get failed: internal server error [code 500]");
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            log.warn("airport get failed: bad request [code 400]");
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 403) {
            log.warn("airport get failed: forbidden access [code 403]");
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 401) {
            log.warn("airport get failed: unauthorized access [code 401]");
            *_output << "Unauthorized access. Please log in." << endl;
        }
    } catch (...) {
        log.error("unknown error");
        *_output << "Unknown error. Call to support" << endl;
    }
}

void AirportPresenter::createAirport() {
    try {

        // Запрос данных у пользователя
        string name;
        int size;
        double x, y;
        try {
            *_output << "Enter airport name: ";
            *_input >> name;

            *_output << "Enter airport size: ";
            string size1;
            *_input >> size1;
            size = stoi(size1);

            *_output << "Enter airport coordinates (x): ";
            string x1;
            *_input >> x1;
            x = stod(x1);

            *_output << "Enter airport coordinates (y): ";
            string y1;
            *_input >> y1;
            y = stod(y1);
        } catch (...) {
            throw 400;
        }
        // Создание модели аэропорта
        AirportModel newAirport(0, name, size, x, y); // ID будет 0, так как это новый аэропорт
        AirportRepository airportRepo;
        string token = TokenRepository().getToken(); // Получаем токен

        // Вызов метода для создания аэропорта
        AirportModel createdAirport = airportRepo.createAirport(newAirport, token);
        log.info("airport create successful: id=" + to_string(createdAirport.getId()) + "[code 200]");
        *_output << "Airport created successfully!" << endl;
        *_output << left; // Выравнивание по левому краю
        *_output << setw(10) << "ID"
                 << setw(10) << "Name"
                 << setw(10) << "Size"
                 << setw(10) << "Coordinates" << endl;

        *_output << setw(10) << createdAirport.getId()
                 << setw(10) << createdAirport.getName()
                 << setw(10) << createdAirport.getSize()
                 << setw(10) << "(" << createdAirport.getX() << ", " << createdAirport.getY() << ")" << endl;

    } catch (const int& status) {
        *_output << "Error creating airport. Status: " << status << endl;
        if (status == 500) {
            log.warn("airport create failed: internal server error [code 500]");
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            log.warn("airport create failed: bad request [code 400]");
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 403) {
            log.warn("airport get failed: forbidden request [code 403]");
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 409) {
            log.warn("airport get failed: conflict [code 409]");
            *_output << "Conflict" << endl;
        } else if (status == 401) {
            log.warn("airport get failed: unauthorized access [code 401]");
            *_output << "Unauthorized access. Please log in." << endl;
        }
    } catch (...) {
        log.error("unknown error");
        *_output << "Unknown error. Call to support" << endl;
    }
}

void AirportPresenter::updateAirport() {
    try {
        long int airportId;
        try {
            string id1;
            *_output << "Enter airport ID to update: ";
            *_input >> id1;
            airportId = stol(id1);
        } catch(...){
            throw 400;
        }

        string newName;
        int newSize;
        double newX, newY;
        set<string> updateFields;
        try {
            string newSize1, newX1, newY1, newName1;
            *_output << "Enter new name (leave - to keep current): ";
            *_input >> newName1;
            if (newName1 != "-"){
                newName = newName1;
                updateFields.insert("name");
            } else
                newName = "";

            *_output << "Enter new size (leave - to keep current): ";
            *_input >> newSize1;
            if (newSize1 != "-"){
                newSize = stoi(newSize1);
                updateFields.insert("size");
            } else
                newSize = -1;

            *_output << "Enter new coordinate x (leave - to keep current): ";
            *_input >> newX1;
            if (newX1 != "-") {
                newX = stoi(newX1);
                updateFields.insert("x");
            } else
                newX = -1;


            *_output << "Enter new coordinate y (leave - to keep current): ";
            *_input >> newY1;
            if (newY1 != "-"){
                newY = stoi(newY1);
                updateFields.insert("y");
            } else
                newY = -1;

        } catch (...) {
            throw 400;
        }
        AirportModel updatedAirport(airportId, newName, newSize, newX, newY);
        AirportRepository airportRepo;
        string token = TokenRepository().getToken(); // Получаем токен

        AirportModel result = airportRepo.updateAirport(updatedAirport, updateFields, token);
        log.info("airport update successful: id=" + to_string(result.getId()) + " [code 200]");
        *_output << "Airport updated successfully!" << endl;
        *_output << left; // Выравнивание по левому краю
        *_output << setw(10) << "ID"
                 << setw(10) << "Name"
                 << setw(10) << "Size"
                 << setw(10) << "Coordinates" << endl;

        *_output << setw(10) << result.getId()
                 << setw(10) << result.getName()
                 << setw(10) << result.getSize()
                 << setw(10) << "(" << result.getX() << ", " << result.getY() << ")" << endl;

    } catch (const int& status) {
        *_output << "Error updating airport. Status: " << status << endl;
        if (status == 500) {
            log.warn("airport update failed: internal server error [code 500]");
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            log.warn("airport update failed: bad request [code 400]");
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 403) {
            log.warn("airport update failed: forbidden request [code 403]");
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 409) {
            log.warn("airport get failed: conflict [code 409]");
            *_output << "Conflict. This airport contains plane or participates in flight" << endl;
        } else if (status == 401) {
            log.warn("airport get failed: unauthorized access [code 401]");
            *_output << "Unauthorized access. Please log in." << endl;
        }
    } catch (...) {
        log.error("unknown error");
        *_output << "Unknown error. Call to support" << endl;
    }
}

void AirportPresenter::deleteAirport() {
    try {
        long int airportId;
        try {
            string id1;
            *_output << "Enter airport ID to delete: ";
            *_input >> id1;
            airportId = stol(id1);
        } catch(...){
            throw 400;
        }

        AirportRepository airportRepo;
        string token = TokenRepository().getToken(); // Получаем токен
        airportRepo.deleteAirport(airportId, token);
        log.info("airport delete successful: id=" + to_string(airportId) + " [code 200]");
        *_output << "Airport deleted successfully" << endl;
    } catch (const int& status) {
        *_output << "Error deleting airport. Status: " << status << endl;
        if (status == 500) {
            log.warn("airport delete failed: internal server error [code 500]");
            *_output << "Internal server error. Please try again later." << endl;
        } else if (status == 400) {
            log.warn("airport delete failed: bad request [code 400]");
            *_output << "Bad request. Please check your input." << endl;
        } else if (status == 403) {
            log.warn("airport delete failed: forbidden access [code 403]");
            *_output << "Forbidden access. You do not have permission." << endl;
        } else if (status == 409) {
            log.warn("airport delete failed: conflict [code 409]");
            *_output << "Conflict. This airport contains plane or participates in flight" << endl;
        } else if (status == 401) {
            log.warn("airport delete failed: unauthorized access [code 401]");
            *_output << "Unauthorized access. Please log in." << endl;
        }
    } catch (...) {
        log.error("unknown error");
        *_output << "Unknown error. Call to support" << endl;
    }
}