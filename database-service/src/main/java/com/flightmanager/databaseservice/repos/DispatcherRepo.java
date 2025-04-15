package com.flightmanager.databaseservice.repos;

import com.flightmanager.databaseservice.models.DispatcherModel;
import org.springframework.data.jpa.repository.JpaRepository;

public interface DispatcherRepo extends JpaRepository<DispatcherModel, Long> {
}
