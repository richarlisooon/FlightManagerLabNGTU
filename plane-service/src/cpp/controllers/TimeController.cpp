#include "../../header/controllers/TimeController.h"
#include <fstream>
#include "../../Config.h"
using namespace std;
using namespace httplib;
void TimeController::configure(Server* server)
{
    server->Get(TIME_GET_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE) {
                log.warn("get time failed: forbidden access [code 403]");
                throw string("403 Forbidden access");
            }
            long int time = serv.getCurrentTime(header);
            res.status = 200;
            res.set_content(to_string(time), "text/plain");
            log.info("get time successful: [code 200]");
        } catch (string& e)
        {
            log.warn(e);
            res.status = stoi(e);
            res.set_content(e, "text/plain");
        } catch (const exception& e)
        {
            string str(e.what());
            log.warn("get time failed: " + str + " [code 500]");
            res.status = 500;
            res.set_content(e.what(), "text/plain");
        } catch (...)
        {
            log.error("unknown error occured");
            res.status = 500;
            res.set_content("unknown error occured", "text/plain");
        }
    });
    server->Post(TIME_SKIP_MAPPING, [this](const Request& req, Response& res)
    {
        try
        {
            auto header = req.get_header_value("Authorization");
            string service_token = req.get_header_value("Service-Token");
            if (service_token != SERVICE_TOKEN_VALUE) {
                log.warn("skip time failed: forbidden access [code 403]");
                throw string("403 Forbidden access");
            }
            long int skip = 0;
            try
            {
                skip = stol(req.get_param_value("skip"));
            } catch (...)
            {
                log.warn("skip time failed: invalid prameter 'skip' [code 400]");
                throw string("400 Invalid parameter skip");
            }
            serv.skipTime(skip, header);
            res.status = 200;
            res.set_content("skipped " + to_string(skip) + " seconds", "text/plain");
            log.info("skip time successful: skip=" + to_string(skip) + " [code 200]");
        } catch (string& e)
        {
            log.warn(e);
            res.status = stoi(e);
            res.set_content(e, "text/plain");
        } catch (const exception& e)
        {
            string str(e.what());
            log.warn("skip time failed: " + str + " [code 500]");
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


