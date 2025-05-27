#include "include/srclib.h"
#include <iostream>

using namespace src;
using namespace std;

int main(int argc, char* argv[])
{
    IdentityPresenter identityPresenter(&cout, &cin);
    bool isAuthenticated = false;

    // Цикл для входа или регистрации
    while (!isAuthenticated) {
        try
        {
            cout << "Select action:" << endl;
            cout << "1. Register" << endl;
            cout << "2. Login" << endl;

            string command;
            cin >> command;

            if (command == "1") {
                isAuthenticated = identityPresenter.registerDispatcher();
                if (isAuthenticated) {
                    cout << "Registration successful! You are now logged in." << endl;
                } else {
                    cout << "Registration failed. Please try again." << endl;
                }
            } else if (command == "2") {
                isAuthenticated = identityPresenter.login();
                if (isAuthenticated) {
                    cout << "Login successful! Welcome back." << endl;
                } else {
                    cout << "Login failed. Please check your credentials." << endl;
                }
            } else {
                cout << "Invalid command! Please select 1 or 2." << endl;
            }
        } catch (...)
        {
            cout << "ERROR" << endl;
        }

    }

    // Основной цикл для управления
    while (true) {
        try{
            cout << "Select action:" << endl;
            cout << "1. Manage Airports" << endl;
            cout << "2. Manage Dispatchers" << endl;
            cout << "3. Manage Flights" << endl;
            cout << "4. Manage Planes" << endl;
            cout << "5. Manage Time" << endl;
            cout << "6. Exit" << endl;

            string command;
            cin >> command;

            if (command == "1") {
                AirportPresenter airportPresenter(&cout, &cin);
                cout << "Select action for Airports:" << endl;
                cout << "1. Get Airport" << endl;
                cout << "2. Create Airport" << endl;
                cout << "3. Update Airport" << endl;
                cout << "4. Delete Airports" << endl;
                string airportAction;
                cin >> airportAction;

                if (airportAction == "1") {
                    airportPresenter.getAirports();
                } else if (airportAction == "2") {
                    airportPresenter.createAirport();
                } else if (airportAction == "3") {
                    airportPresenter.updateAirport();
                } else if (airportAction == "4") {
                    airportPresenter.deleteAirport();
                } else {
                    cout << "Invalid action for Airports!" << endl;
                }
            } else if (command == "2") {
                DispatcherPresenter dispatcherPresenter(&cout, &cin);
                cout << "Select action for Dispatchers:" << endl;
                cout << "1. Get Dispatchers" << endl;
                cout << "2. Get Dispatcher By Id" << endl;
                cout << "3. Update Dispatcher" << endl;
                string dispatcherAction;
                cin >> dispatcherAction;

                if (dispatcherAction == "1") {
                    dispatcherPresenter.getDispatchers();
                } else if (dispatcherAction == "2") {
                    dispatcherPresenter.getDispatcherById();
                } else if (dispatcherAction == "3") {
                    dispatcherPresenter.updateDispatcher();
                } else
                    cout << "Invalid action for Dispatchers!" << endl;
            } else if (command == "3") {
                FlightPresenter flightPresenter(&cout, &cin);
                cout << "Select action for Flights:" << endl;
                cout << "1. Get All Flights" << endl;
                cout << "2. Create Flight" << endl;
                string flightAction;
                cin >> flightAction;

                if (flightAction == "1") {
                    flightPresenter.getAllFlights();
                } else if (flightAction == "2") {
                    flightPresenter.createFlight();
                } else {
                    cout << "Invalid action for Flights!" << endl;
                }
            } else if (command == "4") {
                PlanePresenter planePresenter(&cout, &cin);
                cout << "Select action for Planes:" << endl;
                cout << "1. Get Planes" << endl;
                cout << "2. Create Plane" << endl;
                cout << "3. Update Plane" << endl;
                cout << "4. Delete Plane" << endl;
                string planeAction;
                cin >> planeAction;

                if (planeAction == "1") {
                    planePresenter.getPlanes();
                } else if (planeAction == "2") {
                    planePresenter.createPlane();
                } else if (planeAction == "3") {
                    planePresenter.updatePlane();
                } else if (planeAction == "4") {
                    planePresenter.deletePlane();
                } else {
                    cout << "Invalid action for Planes!" << endl;
                }
            } else if (command == "5") {
                TimePresenter timePresenter(&cout, &cin);
                cout << "Select action for Time Management:" << endl;
                cout << "1. Set Time" << endl;
                cout << "2. Get Current Time" << endl;
                string timeAction;
                cin >> timeAction;

                if (timeAction == "1") {
                    timePresenter.addTime();
                } else if (timeAction == "2") {
                    timePresenter.getCurrentTime();
                } else {
                    cout << "Invalid action for Time Management!" << endl;
                }
            } else if (command == "6") {
                cout << "Exiting the program." << endl;
                break; // Выход из программы
            } else {
                cout << "Invalid command! Please select a valid option." << endl;
            }
        } catch (...)
        {
            cout << "ERROR" << endl;
        }
    }

    return 0;
}

