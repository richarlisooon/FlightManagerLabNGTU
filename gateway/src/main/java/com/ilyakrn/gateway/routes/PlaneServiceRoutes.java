package com.ilyakrn.gateway.routes;

import lombok.Getter;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Configuration;

@Configuration
public class PlaneServiceRoutes {
    @Getter
    @Value("${url.plane-service}")
    private String url;


    @Value("${mapping.airport.getAll}")
    private String airportGetAllMapping;
    @Value("${mapping.airport.get}")
    private String airportGetMapping;
    @Value("${mapping.airport.create}")
    private String airportCreateMapping;
    @Value("${mapping.airport.update}")
    private String airportUpdateMapping;
    @Value("${mapping.airport.delete}")
    private String airportDeleteMapping;

    @Value("${mapping.plane.getAll}")
    private String planeGetAllMapping;
    @Value("${mapping.plane.get}")
    private String planeGetMapping;
    @Value("${mapping.plane.create}")
    private String planeCreateMapping;
    @Value("${mapping.plane.update}")
    private String planeUpdateMapping;
    @Value("${mapping.plane.delete}")
    private String planeDeleteMapping;

    @Value("${mapping.dispatcher.getAll}")
    private String dispatcherGetAllMapping;
    @Value("${mapping.dispatcher.get}")
    private String dispatcherGetMapping;
    @Value("${mapping.dispatcher.update}")
    private String dispatcherUpdateMapping;

    @Value("${mapping.flights.getAll}")
    private String flightsGetAllMapping;
    @Value("${mapping.flights.get}")
    private String flightsGetMapping;
    @Value("${mapping.flights.create}")
    private String flightsCreateMapping;

    @Value("${mapping.time.get}")
    private String timeGetMapping;
    @Value("${mapping.time.skip}")
    private String timeSkipMapping;

    public String[] getMappings() {
        return new String[]{
                airportGetAllMapping,
                airportGetMapping,
                airportCreateMapping,
                airportUpdateMapping,
                airportDeleteMapping,

                planeGetAllMapping,
                planeGetMapping,
                planeCreateMapping,
                planeUpdateMapping,
                planeDeleteMapping,

                dispatcherGetAllMapping,
                dispatcherGetMapping,
                dispatcherUpdateMapping,

                flightsGetAllMapping,
                flightsGetMapping,
                flightsCreateMapping,

                timeGetMapping,
                timeSkipMapping
        };
    }
}
