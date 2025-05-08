package com.flightmanager.identityservice.config;

import lombok.Getter;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Configuration;

@Getter
@Configuration
public class PropertiesConfig {

    @Value("${jwt.signing.key}")
    private String jwtSecret;


    @Value("${mapping.dispatcher.get}")
    private String userGet;
    @Value("${mapping.dispatcher.create}")
    private String userCreate;

    @Value("${url.database-service}")
    private String databaseServiceUrl;
}
