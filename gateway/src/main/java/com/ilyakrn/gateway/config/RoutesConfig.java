package com.ilyakrn.gateway.config;

import com.ilyakrn.gateway.routes.IdentityServiceRoutes;
import com.ilyakrn.gateway.routes.PlaneServiceRoutes;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cloud.gateway.route.RouteLocator;
import org.springframework.cloud.gateway.route.builder.RouteLocatorBuilder;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class RoutesConfig {
    private final Logger log = LogManager.getLogger(RoutesConfig.class);
    @Autowired
    IdentityServiceRoutes identityServiceRoutes;
    @Autowired
    PlaneServiceRoutes planeServiceRoutes;
    @Autowired
    PropertiesConfig cfg;

    @Bean
    public RouteLocator routes(RouteLocatorBuilder builder) {
        RouteLocatorBuilder.Builder b = builder.routes();
        try {

            String[] mappingsIdentity = identityServiceRoutes.getMappings();
            for (String mapping : mappingsIdentity) {
                log.debug("Configuring route for Identity Service: Path={}, Target URL={}", mapping, identityServiceRoutes.getUrl());

                b = b.route(p -> p
                        .path(mapping)
                        .filters(f -> f.addRequestHeader(cfg.getServiceTokenHeader(), cfg.getServiceToken()))
                        .uri(identityServiceRoutes.getUrl()));
                log.info("added route: Path={}, Target URL={}", identityServiceRoutes.getUrl(), mapping);
            }

            String[] mappingsPlane = planeServiceRoutes.getMappings();
            for (String mapping : mappingsPlane) {
                log.debug("Configuring route for Plane Service: Path={}, Target URL={}", mapping, planeServiceRoutes.getUrl());
                b = b.route(p -> p
                        .path(mapping)
                        .filters(f -> f.addRequestHeader(cfg.getServiceTokenHeader(), cfg.getServiceToken()))
                        .uri(planeServiceRoutes.getUrl()));
                log.info("added route: Path={}, Target URL={}", planeServiceRoutes.getUrl(), mapping);
            }
            log.debug("All routes configured successfully.");
        } catch (Exception e) {
            log.error("Route configuration failed: {}", e.getMessage());
        }

        return b.build();
    }
}
