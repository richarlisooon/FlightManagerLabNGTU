package com.flightmanager.databaseservice.api;

import com.flightmanager.databaseservice.models.PlaneModel;
import com.flightmanager.databaseservice.repos.PlaneRepo;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;


@RestController
public class PlaneController {
    private final Logger log = LogManager.getLogger(PlaneController.class);

    @Autowired
    private PlaneRepo repo;


    @GetMapping("${mapping.plane.get}")
    public ResponseEntity<List<PlaneModel>> get(
            @RequestParam(value = "id", required = false) Long id,
            @RequestParam(value = "name", required = false) String name,
            @RequestParam(value = "pilot", required = false) String pilot,
            @RequestParam(value = "builtYear", required = false) Integer builtYear,
            @RequestParam(value = "brokenPercentage", required = false) Integer brokenPercentage,
            @RequestParam(value = "speed", required = false) Integer speed,
            @RequestParam(value = "minAirportSize", required = false) Integer minAirportSize
    ) {
        try {
            List<PlaneModel> models = repo.findAll();
            if (id != null)
                models = models.stream().filter(m -> m.getId().equals(id)).collect(Collectors.toList());
            if (name != null)
                models = models.stream().filter(m -> m.getName().equals(name)).collect(Collectors.toList());
            if (pilot != null)
                models = models.stream().filter(m -> m.getPilot().equals(pilot)).collect(Collectors.toList());
            if (builtYear != null)
                models = models.stream().filter(m -> m.getBuiltYear().equals(builtYear)).collect(Collectors.toList());
            if (brokenPercentage != null)
                models = models.stream().filter(m -> m.getBrokenPercentage().equals(brokenPercentage)).collect(Collectors.toList());
            if (speed != null)
                models = models.stream().filter(m -> m.getSpeed().equals(speed)).collect(Collectors.toList());
            if (minAirportSize != null)
                models = models.stream().filter(m -> m.getMinAirportSize().equals(minAirportSize)).collect(Collectors.toList());
            log.info("get plane successful ({} entities) [code 200]", models.size());
            return ResponseEntity.ok(models);
        } catch (Exception e) {
            log.debug("Error get plane retrial:{}" + e.getMessage()+ ",input parameters:id={}" + id + ", name={}" + name + ", pilot={}" + pilot + ", builtYear={}" + builtYear + ", brokenPercentage={}" + brokenPercentage + "speed={}" + speed + ", minAirportSize={} "+ minAirportSize);
            log.warn("get plane failed: {} [code 500]", e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.plane.create}")
    public ResponseEntity<PlaneModel> create(@RequestBody PlaneModel data) {
        try {
            data.setId(0L);
            if (containsNullFields(data)) {
                log.warn("create plane failed: invalid data [code 400]");
                return ResponseEntity.status(400).build();
            }
            PlaneModel model = repo.save(data);
            log.info("create plane successful: id={} [code 200]", model.getId());
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            log.debug("Error creating plane:{}" + e.getMessage() + ",input data={}"+ data);
            log.warn("create plane failed: {} [code 500]", e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.plane.update}")
    public ResponseEntity<PlaneModel> update(@RequestBody PlaneModel data, @RequestParam("update") String update) {
        try {
            if (data.getId() == null) {
                log.warn("update plane failed: id not provided [code 400]");
                return ResponseEntity.status(400).build();
            }
            PlaneModel fromDB = repo.findById(data.getId()).orElse(null);
            if (fromDB == null) {
                log.warn("update plane failed: plane not found [code 400]");
                return ResponseEntity.status(400).build();
            }

            ArrayList<String> fields = new ArrayList<>(Arrays.asList(update.split(",")));
            if (!fields.contains("name"))
                data.setName(fromDB.getName());
            if (!fields.contains("pilot"))
                data.setPilot(fromDB.getPilot());
            if (!fields.contains("builtYear"))
                data.setBuiltYear(fromDB.getBuiltYear());
            if (!fields.contains("brokenPercentage"))
                data.setBrokenPercentage(fromDB.getBrokenPercentage());
            if (!fields.contains("speed"))
                data.setSpeed(fromDB.getSpeed());
            if (!fields.contains("minAirportSize"))
                data.setMinAirportSize(fromDB.getMinAirportSize());
            if (containsNullFields(data)) {
                log.warn("update plane failed: invalid data [code 400]");
                return ResponseEntity.status(400).build();
            }

            PlaneModel model = repo.save(data);
            log.info("update plane successful: id={} [code 200]", model.getId());
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            log.debug("Error plane update:{}" + e.getMessage() + ",input data: {}" + data + ", update fields: {}" + update);
            log.warn("update plane failed: {} [code 500]", e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @DeleteMapping("${mapping.plane.delete}/{id}")
    public ResponseEntity<Void> delete(@PathVariable("id") long id) {
        try {
            repo.deleteById(id);
            log.info("delete plane successful: id={} [code 200]", id);
            return ResponseEntity.ok().build();
        } catch (EmptyResultDataAccessException e) {
            log.warn("delete plane failed: id={} not exists [code 200]", id);
            return ResponseEntity.ok().build();
        } catch (Exception e) {
            log.debug("Error plane delete:{}" +  e.getMessage() + ",input parameters:id={}" + id);
            log.warn("delete plane failed: {} [code 500]", e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    private boolean containsNullFields(PlaneModel data) {
        return data.getName() == null ||
                data.getPilot() == null ||
                data.getBuiltYear() == null ||
                data.getBrokenPercentage() == null ||
                data.getSpeed() == null ||
                data.getMinAirportSize() == null ||
                data.getName().isEmpty() ||
                data.getPilot().isEmpty();
    }

}
