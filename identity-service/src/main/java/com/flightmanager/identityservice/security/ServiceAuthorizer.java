package com.flightmanager.identityservice.security;

import com.flightmanager.identityservice.config.PropertiesConfig;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class ServiceAuthorizer {
    private final Logger log = LogManager.getLogger(ServiceAuthorizer.class);


    @Autowired
    private PropertiesConfig properties;

    public boolean authorize(String token) {
        log.debug("Received token: {}", token);
        log.debug("Expected service token: {}", properties.getServiceToken());

        boolean isAuthorized = token.equals(properties.getServiceToken());
        log.debug("Authorization result: {}", isAuthorized ? "SUCCESS" : "FAILURE");

        return isAuthorized;
    }
}
