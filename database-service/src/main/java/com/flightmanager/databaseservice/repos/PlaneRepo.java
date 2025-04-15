package com.flightmanager.databaseservice.repos;

import com.flightmanager.databaseservice.models.PlaneModel;
import org.springframework.data.jpa.repository.JpaRepository;

public interface PlaneRepo extends JpaRepository<PlaneModel, Long> {
}
