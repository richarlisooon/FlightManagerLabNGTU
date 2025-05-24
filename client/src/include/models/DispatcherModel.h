#pragma once

#include <string>
#include <set>
#include "RoleModel.h"

namespace src
{
    class DispatcherModel
    {
        long int _id;
        std::string _firstname;
        std::string _lastname;
        std::string _email;
        std::string _password;
        bool _isBanned;
        std::set<RoleModel> _roles;
    public:
        DispatcherModel(long int id, std::string firstname, std::string lastname, std::string email, std::string password, bool isBanned, std::set<RoleModel> roles);

        long int getId();
        std::string getFirstname();
        std::string getLastname();
        std::string getEmail();
        std::string getPassword();
        bool getIsBanned();
        std::set<RoleModel> getRoles();

        void setId(long int id);
        void setFirstname(std::string firstname);
        void setLastname(std::string lastname);
        void setEmail(std::string email);
        void setPassword(std::string password);
        void setIsBanned(bool isBanned);
        void setRoles(std::set<RoleModel> roles);

    };
}