package com.flightmanager.databaseservice.repos;

import com.flightmanager.databaseservice.models.AirportModel;
import org.springframework.data.jpa.repository.JpaRepository;

public interface AirportRepo extends JpaRepository<AirportModel, Long> {
}
