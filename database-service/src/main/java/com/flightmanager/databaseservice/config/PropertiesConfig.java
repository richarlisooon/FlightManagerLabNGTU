package com.flightmanager.databaseservice.config;

import lombok.Getter;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Configuration;

@Getter
@Configuration
public class PropertiesConfig {
    @Value("${security.service-token}")
    private String serviceToken;
    @Value("${security.service-token.header}")
    private String serviceTokenHeader;

}
