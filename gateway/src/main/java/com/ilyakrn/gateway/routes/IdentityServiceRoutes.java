package com.ilyakrn.gateway.routes;

import lombok.Getter;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Configuration;

@Configuration
public class IdentityServiceRoutes {
    @Getter
    @Value("${url.identity-service}")
    private String url;

    @Value("${mapping.auth.login}")
    private String authLoginMapping;
    @Value("${mapping.auth.register}")
    private String authRegisterMapping;

    public String[] getMappings() {
        return new String[]{
                authLoginMapping,
                authRegisterMapping
        };
    }
}
