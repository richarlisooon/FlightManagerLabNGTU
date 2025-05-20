#include "../../header/controllers/TimeController.h"

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
                throw 403;
            }
            long int time = serv.getCurrentTime(header);
            res.status = 200;
            res.set_content(to_string(time), "text/plain");
            log.info("get time successful: [code 200]");
        } catch (int& e)
        {
            log.warn("get time failed: [code " + to_string(e) + "]");
            res.status = e;
        } catch (const exception& e)
        {
            string str(e.what());
            log.warn("get time failed: " + str + " [code 500]");
            res.status = 500;
        } catch (...)
        {
            log.error("unknown error occured");
            res.status = 500;
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
                throw 403;
            }
            long int skip = 0;
            try
            {
                skip = stol(req.get_param_value("skip"));
            } catch (...)
            {
                log.warn("skip time failed: invalid prameter 'skip' [code 400]");
                throw 400;
            }
            serv.skipTime(skip, header);
            res.status = 200;
            res.set_content("skipped " + to_string(skip) + " seconds", "text/plain");
            log.info("skip time successful: skip=" + to_string(skip) + " [code 200]");
        } catch (int& e)
        {
            log.warn("skip time failed: [code " + to_string(e) + "]");
            res.status = e;
        } catch (const exception& e)
        {
            string str(e.what());
            log.warn("skip time failed: " + str + " [code 500]");
            res.status = 500;
        } catch (...)
        {
            log.error("unknown error occured");
            res.status = 500;
        }
    });
}

