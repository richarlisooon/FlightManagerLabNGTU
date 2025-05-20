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
    private IdentityServiceRoutes identityServiceRoutes;

    @Autowired
    private PlaneServiceRoutes planeServiceRoutes;

    @Autowired
    private PropertiesConfig propertiesConfig;

    @Bean
    public RouteLocator routes(RouteLocatorBuilder builder) {
        RouteLocatorBuilder.Builder routesBuilder = builder.routes();

        try {
            for (String mapping : identityServiceRoutes.getMappings()) {
                log.debug("Configuring route for Identity Service: Path={}, Target URL={}",
                    mapping, identityServiceRoutes.getUrl());

                routesBuilder = routesBuilder.route(p -> p
                    .path(mapping)
                    .filters(f -> f.addRequestHeader(
                        propertiesConfig.getServiceTokenHeader(),
                        propertiesConfig.getServiceToken()))
                    .uri(identityServiceRoutes.getUrl()));

                log.info("Added route: Path={}, Target URL={}",
                    mapping, identityServiceRoutes.getUrl());
            }

            for (String mapping : planeServiceRoutes.getMappings()) {
                log.debug("Configuring route for Plane Service: Path={}, Target URL={}",
                    mapping, planeServiceRoutes.getUrl());

                routesBuilder = routesBuilder.route(p -> p
                    .path(mapping)
                    .filters(f -> f.addRequestHeader(
                        propertiesConfig.getServiceTokenHeader(),
                        propertiesConfig.getServiceToken()))
                    .uri(planeServiceRoutes.getUrl()));

                log.info("Added route: Path={}, Target URL={}",
                    mapping, planeServiceRoutes.getUrl());
            }

            log.debug("All routes configured successfully.");
        } catch (Exception e) {
            log.error("Route configuration failed: {}", e.getMessage());
        }

        return routesBuilder.build();
    }
}
