#include "../../header/repos/DispatcherRepository.h"
#include "../../Config.h"
#include <cpp-httplib/httplib.h>
#include <json/single_include/nlohmann/json.hpp>

using namespace std;
using namespace httplib;
using namespace nlohmann;
list<DispatcherModel> DispatcherRepository::getDispatchers(long int* id, string* firstName, string* lastName, string* email, string* password, bool* isBanned, set<RoleModel*>* roles)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);


}
DispatcherModel DispatcherRepository::updateDispatchers(DispatcherModel dispatcher, set<string> updates)
{
    Client cli(DATABASE_SERVICE_HOST_PORT);


}

