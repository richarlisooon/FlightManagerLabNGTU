#include "../../include/presentation/IdentityPresenter.h"
#include "../../include/repos/IdentityRepository.h"
#include "../../include/repos/TokenRepository.h"

using namespace src;
using namespace std;

bool IdentityPresenter::login()
{
    string email, password;

    *_output << "Enter your email: ";
    *_input >> email;

    *_output << "Enter your password: ";
    *_input >> password;

    IdentityRepository identityRepo;

    try
    {
        set<string> loginInfo = identityRepo.login(email, password);
        // Предполагаем, что получаем id и token
        string userId = *loginInfo.begin();
        string token = *(++loginInfo.begin());

        *_output << "Login successful!" << endl;
        *_output << "User   ID: " << userId << endl;
        *_output << "Token: " << token << endl;

        // Сохраняем токен и ID пользователя для дальнейшего использования
        TokenRepository tokenRepo;
        tokenRepo.setTokenAndUserId(token, stol(userId));
        log.info("login successful: id=" + userId + " [code 200]");
        *_output << "Token and User ID saved successfully." << endl;
        return true; // Успешный вход
    }
    catch (const int& status)
    {
        // Обработка ошибок
        switch (status)
        {
        case 500:
            log.warn("login failed: internal server error [code 500]");
            *_output << "Internal server error. Please try again later." << endl;
            break;
        case 400:
            log.warn("login failed: ad request [code 400]");
            *_output << "Wrong request. Please check your input." << endl;
            break;
        case 403:
            log.warn("login failed: forbidden access [code 403]");
            *_output << "Forbidden access. You do not have permission." << endl;
            break;
        case 401:
            log.warn("login failed: unauthorized access [code 401]");
            *_output << "Unauthorized access. Check your credentials." << endl;
            break;
        default:
            log.error("unknown error");
            *_output << "An unexpected error occurred. Please contact support." << endl;
            break;
        }
        return false; // Неудачный вход
    }
}

bool IdentityPresenter::registerDispatcher()
{
    string firstName, lastName, email, password;

    *_output << "Enter first name: ";
    *_input >> firstName;

    *_output << "Enter last name: ";
    *_input >> lastName;

    *_output << "Enter email: ";
    *_input >> email;

    *_output << "Enter password: ";
    *_input >> password;

    // Создаем объект DispatcherModel
    DispatcherModel newDispatcher(0, firstName, lastName, email, password, false, set<RoleModel>());

    IdentityRepository identityRepo;

    try
    {
        set<string> registrationInfo = identityRepo.regist(newDispatcher);
        string userId = *registrationInfo.begin();
        string token = *(++registrationInfo.begin());

        *_output << "Registration successful!" << endl;
        *_output << "User ID: " << userId << endl;
        *_output << "Token: " << token << endl;

        //Сохраняем токен и ID пользователя для дальнейшего использования
        TokenRepository tokenRepo;
        tokenRepo.setTokenAndUserId(token, stol(userId));
        log.info("register successful: id=" + userId + " [code 200]");
        *_output << "Token and User ID saved successfully." << endl;
        return true; // Успешная регистрация
    }
    catch (const int& status)
    {
        // Обработка ошибок
        switch (status)
        {
        case 500:
            log.warn("register failed: internal server error [code 500]");
            *_output << "Internal server error. Please try again later." << endl;
            break;
        case 400:
            log.warn("register failed: bad request [code 400]");
            *_output << "Wrong request. Please check your input." << endl;
            break;
        case 403:
            log.warn("register failed: forbidden access [code 403]");
            *_output << "Forbidden access. You do not have permission." << endl;
            break;
        case 409:
            log.warn("register failed: conflict [code 409]");
            *_output << "Conflict! This dispatcher ID may already exist." << endl;
            break;
        case 401:
            log.warn("register failed: unauthorized access [code 401]");
            *_output << "Unauthorized access. Check your credentials." << endl;
            break;
        default:
            log.warn("unknown error");
            *_output << "An unexpected error occurred. Please contact support." << endl;
            break;
        }
        return false; // Неудачная регистрация
    }
}
