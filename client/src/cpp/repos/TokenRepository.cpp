#include "../../include/repos/TokenRepository.h"
#include "../../include/Config.h"

#include <fstream>
#include <iostream>

using namespace src;
using namespace std;

string TokenRepository::getToken()
{
    ifstream file(TOKEN_FILE_PATH);
    string token;
    if (getline(file, token))
    {
        return token; // Возвращаем токен
    } // Если токен не найден, возвращаем пустую строку
    return "";
}

long int TokenRepository::getUserId()
{
    ifstream file(TOKEN_FILE_PATH);
    string line;
    long int userId = 0;

    // Считываем токен и ID пользователя
    if (getline(file, line) && getline(file, line))
    {
        userId = stol(line); // Преобразуем ID пользователя в long int
    }
    return userId; // Возвращаем ID пользователя
}

bool TokenRepository::setTokenAndUserId(const string& token, long int userId)
{
    ofstream file(TOKEN_FILE_PATH, ios::trunc);
    if (file.is_open())
    {
        // Открываем файл для записи, очищая его
        file << token << endl; // Записываем токен
        file << userId << endl;
        file.close();
        return true; // Успешно записано
    }
    return false;
}
