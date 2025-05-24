#pragma once

#include <string>
namespace src
{
    class TokenRepository {
    public:
        std::string getToken();
        long int getUserId();
        bool setTokenAndUserId(const std::string& token, long int userId);
    };
}