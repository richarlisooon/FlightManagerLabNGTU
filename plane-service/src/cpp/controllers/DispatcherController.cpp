#include "../../header/controllers/DispatcherController.h"
#include "../../Config.h"
#include <json/single_include/nlohmann/json.hpp>



using namespace nlohmann;
using namespace httplib;
using namespace std;


void DispatcherController::configure(Server* server)
{
    // sample request handlers
    server->Get(DISPATCHER_GET_ALL_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE) {
                log.warn("get dispatchers failed: forbidden access [code 403]");
                throw string("403 Forbidden access");
            }
            list<DispatcherModel> dispatchers = serv.getAllDispatchers(header);
            json dispatchers_json = json::array();
            for (auto dispatcher : dispatchers)
            {
                json dispatcher_json;
                dispatcher_json["id"] = dispatcher.getId();
                dispatcher_json["firstName"] = dispatcher.getFirstname();
                dispatcher_json["lastName"] = dispatcher.getLastname();
                dispatcher_json["email"] = dispatcher.getEmail();
                dispatcher_json["password"] = dispatcher.getPassword();
                dispatcher_json["isBanned"] = dispatcher.getIsBanned();
                dispatcher_json["roles"] = json::array();
                for (auto role: dispatcher.getRoles())
                {
                    switch (role)
                    {
                    case RoleModel::ADMIN: dispatcher_json["roles"].push_back("ADMIN");
                    case RoleModel::DISPATCHER: dispatcher_json["roles"].push_back("DISPATCHER");
                    }
                }
                dispatchers_json.push_back(dispatcher_json);
            }
            res.set_content(dispatchers_json.dump(), "application/json");
            res.status = 200;
            log.info("get dispatchers successful: (" + to_string(dispatchers_json.size()) + " entities) [code 200]");
        }  catch (int& e)
        {
            log.warn("get dispatchers failed: [code " + to_string(e) + "]");
            res.status = e;
        } catch (const exception& e)
        {
            string str(e.what());
            log.warn("get dispatchers failed: " + str + " [code 500]");
            res.status = 500;
        } catch (...)
        {
            log.error("unknown error occured");
            res.status = 500;
        }
    });
    server->Post(DISPATCHER_UPDATE_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE) {
                log.warn("update dispatcher failed: forbidden access [code 403]");
                throw string("403 Forbidden access");
            }
            string fields;
            try
            {
                fields = req.get_param_value("update");
            } catch (...)
            {
                log.warn("update dispatcher failed: wrong parameter 'update' [code 400]");
                throw string("400 Invalid parameter update");
            }
            stringstream ss(fields);
            string item;
            set<string> updates;
            while (getline(ss, item, ','))
            {
                item.erase(0, item.find_first_not_of(" \n\r\t"));
                item.erase(item.find_last_not_of(" \n\r\t") + 1);
                if (!item.empty())
                    updates.insert(item);
            }
            json request;
            try
            {
                request = json::parse(req.body);
            } catch (...)
            {
                log.warn("update dispatcher failed: invalid data [code 400]");
                throw string("400 Bad request");
            }
            for (auto update : updates)
            {
                if (request[update].is_null())
                {
                    log.warn("update dispatcher failed:  fields to update not provided [code 400]");
                    throw string("400 Fields to update not provided");
                }

                if (request["id"].is_null())
                {
                    log.warn("update dispatcher failed: id is not provided [code 400]");
                    throw string("400 Id not provided");
                }

            }
            set<RoleModel> roles;
            bool isBanned;
            string firstName, lastName, email, password;
            try
            {
                if (!request["roles"].is_null())
                {
                    for (auto role : request["roles"])
                    {
                        if (role == "ADMIN")
                            roles.insert(RoleModel::ADMIN);
                        else if (role == "DISPATCHER")
                            roles.insert(RoleModel::DISPATCHER);
                    }
                } else
                    roles = set<RoleModel>();
                if (!request["isBanned"].is_null()) isBanned = request["isBanned"]; else isBanned = false;
                if (!request["lastName"].is_null()) lastName = request["lastName"]; else lastName = "string";
                if (!request["firstName"].is_null()) firstName = request["firstName"]; else firstName = "string";
                if (!request["email"].is_null()) email = request["email"]; else email = "string";
                if (!request["password"].is_null()) password = request["password"]; else password = "string";
            } catch (...)
            {
                log.warn("update dispatcher failed: invalid data [code 400]");
                throw string("400 Invalid data");
            }
            DispatcherModel dispatcher(request["id"], firstName, lastName, email, password, isBanned, roles);
            DispatcherModel updated = serv.updateDispatcher(dispatcher, updates, header);
            updates.clear();
            json dispatcher_json;
            dispatcher_json["id"] = updated.getId();
            dispatcher_json["firstName"] = updated.getFirstname();
            dispatcher_json["lastName"] = updated.getLastname();
            dispatcher_json["email"] = updated.getEmail();
            dispatcher_json["password"] = updated.getPassword();
            dispatcher_json["isBanned"] = updated.getIsBanned();
            dispatcher_json["roles"] = json::array();
            for (auto role: updated.getRoles())
            {
                switch (role)
                {
                case RoleModel::ADMIN: dispatcher_json["roles"].push_back("ADMIN");
                case RoleModel::DISPATCHER: dispatcher_json["roles"].push_back("DISPATCHER");
                }
            }
            res.status = 200;
            res.set_content(dispatcher_json.dump(), "application/json");
            log.info("update dispatcher successful: id=" + to_string(dispatcher_json["id"]) + " [code 200]");
        } catch (string& e)
        {
            log.warn(e);
            res.status = stoi(e);
            res.set_content(e, "text/plain");
        } catch (const exception& e)
        {
            string str(e.what());
            log.warn("update dispatcher failed: " + str + " [code 500]");
            res.status = 500;
            res.set_content(e.what(), "text/plain");
        } catch (...)
        {
            log.error("unknown error occured");
            res.status = 500;
            res.set_content("unknown error occured", "text/plain");
        }
    });
    server->Get(DISPATCHER_GET_BY_ID_MAPPING, [&](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            auto isPrivate = req.get_param_value("private");
            if (service_token != SERVICE_TOKEN_VALUE) {
                log.warn("get dispatcher failed: forbidden access [code 403]");
                throw string("403 Forbidden access");
            }
            long int id;
            try
            {
                id = stol(req.get_param_value("id"));
            } catch (...)
            {
                log.warn("get dispatcher failed: invalid parameter [code 400]");
                throw string("400 Invalid parameter id");
            }
            DispatcherModel dispatcher = serv.getDispatcherById(id, header, isPrivate == "true");
            json dispatcher_json;
            dispatcher_json["id"] = dispatcher.getId();
            dispatcher_json["firstName"] = dispatcher.getFirstname();
            dispatcher_json["lastName"] = dispatcher.getLastname();
            dispatcher_json["email"] = dispatcher.getEmail();
            dispatcher_json["password"] = dispatcher.getPassword();
            dispatcher_json["isBanned"] = dispatcher.getIsBanned();
            dispatcher_json["roles"] = json::array();
            for (auto role: dispatcher.getRoles())
            {
                switch (role)
                {
                case RoleModel::ADMIN: dispatcher_json["roles"].push_back("ADMIN");
                case RoleModel::DISPATCHER: dispatcher_json["roles"].push_back("DISPATCHER");
                }
            }
            res.status = 200;
            res.set_content(dispatcher_json.dump(), "application/json");
            log.info("get dispatcher successful: id=" + to_string(id) + " [code 200]");
        }  catch (string& e)
        {
            log.warn(e);
            res.status = stoi(e);
            res.set_content(e, "text/plain");
        } catch (const exception& e)
        {
            string str(e.what());
            log.warn("get dispatcher failed: " + str + " [code 500]");
            res.status = 500;
            res.set_content(e.what(), "text/plain");
        } catch (...)
        {
            log.error("unknown error occured");
            res.status = 500;
            res.set_content("unknown error occured", "text/plain");
        }
    });
}
