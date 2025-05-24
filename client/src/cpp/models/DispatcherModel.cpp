#include "../../include/models/DispatcherModel.h"

using namespace src;
using namespace std;

DispatcherModel::DispatcherModel(long int id, string firstname, string lastname, string email, string password, bool isBanned, set<RoleModel> roles)
{
    _id = id;
    _firstname = firstname;
    _lastname = lastname;
    _email = email;
    _password = password;
    _isBanned = isBanned;
    _roles = roles;
}

long int DispatcherModel::getId()
{
    return _id;
}
string DispatcherModel::getFirstname()
{
    return _firstname;
}
string DispatcherModel::getLastname()
{
    return _lastname;
}
string DispatcherModel::getEmail()
{
    return _email;
}
string DispatcherModel::getPassword()
{
    return _password;
}
bool DispatcherModel::getIsBanned()
{
    return _isBanned;
}
set<RoleModel> DispatcherModel::getRoles()
{
    return _roles;
}


void DispatcherModel::setId(long int id)
{
    _id = id;
}
void DispatcherModel::setFirstname(string firstname)
{
    _firstname = firstname;
}
void DispatcherModel::setLastname(string lastname)
{
    _lastname = lastname;
}
void DispatcherModel::setEmail(string email)
{
    _email = email;
}
void DispatcherModel::setPassword(string password)
{
    _password = password;
}
void DispatcherModel::setIsBanned(bool isBanned)
{
    _isBanned = isBanned;
}
void DispatcherModel::setRoles(set<RoleModel> roles)
{
    _roles = roles;
}


