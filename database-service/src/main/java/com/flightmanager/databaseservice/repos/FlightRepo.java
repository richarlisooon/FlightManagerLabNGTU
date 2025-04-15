package com.flightmanager.databaseservice.repos;

import com.flightmanager.databaseservice.models.FlightModel;
import org.springframework.data.jpa.repository.JpaRepository;

public interface FlightRepo extends JpaRepository<FlightModel, Long> {
}
