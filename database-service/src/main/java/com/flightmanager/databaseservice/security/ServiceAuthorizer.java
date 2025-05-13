package com.flightmanager.databaseservice.security;

import com.flightmanager.databaseservice.config.PropertiesConfig;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class ServiceAuthorizer {
    private final Logger log = LogManager.getLogger(ServiceAuthorizer.class);


    @Autowired
    private PropertiesConfig properties;

    public boolean authorize(String token) {
        boolean isAuthorized = token.equals(properties.getServiceToken());
        log.debug("Authorization result: " + (isAuthorized ? "SUCCESS" : "FAILURE"));

        return isAuthorized;
    }
}


