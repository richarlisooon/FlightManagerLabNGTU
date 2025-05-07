package com.flightmanager.databaseservice.api;

import com.flightmanager.databaseservice.models.AirportModel;
import com.flightmanager.databaseservice.repos.AirportRepo;
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
public class AirportController {
    private final Logger log = LogManager.getLogger(AirportController.class);

    @Autowired
    private AirportRepo repo;


    @GetMapping("${mapping.airport.get}")
    public ResponseEntity<List<AirportModel>> get(
            @RequestParam(value = "id", required = false) Long id,
            @RequestParam(value = "name", required = false) String name,
            @RequestParam(value = "x", required = false) Double x,
            @RequestParam(value = "y", required = false) Double y,
            @RequestParam(value = "size", required = false) Integer size
    ) {
        try {
            List<AirportModel> models = repo.findAll();
            if (id != null)
                models = models.stream().filter(m -> m.getId().equals(id)).collect(Collectors.toList());
            if (name != null)
                models = models.stream().filter(m -> m.getName().equals(name)).collect(Collectors.toList());
            if (x != null)
                models = models.stream().filter(m -> m.getX().equals(x)).collect(Collectors.toList());
            if (y != null)
                models = models.stream().filter(m -> m.getY().equals(y)).collect(Collectors.toList());
            if (size != null)
                models = models.stream().filter(m -> m.getSize().equals(size)).collect(Collectors.toList());
            log.info("get airports successful ({} entities) [code 200]", models.size());
            return ResponseEntity.ok(models);
        } catch (Exception e) {
            log.debug("Error get airport retrial:{}" + e.getMessage()+ ",input parameters:id={}" + id + ", name={}" + name + ", x={}" + x + ", y={}" + y + ", size={}" + size );
            log.warn("get airports failed: {} [code 500]", e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.airport.create}")
    public ResponseEntity<AirportModel> create(@RequestBody AirportModel data) {
        try {
            data.setId(0L);
            if (containsNullFields(data)) {
                log.warn("create airport failed: invalid data [code 400]");
                return ResponseEntity.status(400).build();
            }
            AirportModel model = repo.save(data);
            log.info("create airport successful: id={} [code 200]", model.getId());
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            log.debug("Error creating airport:{}" + e.getMessage() + ",input data={}"+ data);
            log.warn("create airport failed: {} [code 500]", e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.airport.update}")
    public ResponseEntity<AirportModel> update(@RequestBody AirportModel data, @RequestParam("update") String update) {
        try {
            if (data.getId() == null) {
                log.warn("update airport failed: id not provided [code 400]");
                return ResponseEntity.status(400).build();
            }
            AirportModel fromDB = repo.findById(data.getId()).orElse(null);
            if (fromDB == null) {
                log.warn("update airport failed: airport not found [code 400]");
                return ResponseEntity.status(400).build();
            }

            ArrayList<String> fields = new ArrayList<>(Arrays.asList(update.split(",")));
            if (!fields.contains("name"))
                data.setName(fromDB.getName());
            if (!fields.contains("x"))
                data.setX(fromDB.getX());
            if (!fields.contains("y"))
                data.setY(fromDB.getY());
            if (!fields.contains("size"))
                data.setSize(fromDB.getSize());
            if (containsNullFields(data)) {
                log.warn("update airport failed: invalid data [code 400]");
                return ResponseEntity.status(400).build();
            }

            AirportModel model = repo.save(data);
            log.info("update airport successful: id={} [code 200]", model.getId());
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            log.debug("Error airport update:{}" + e.getMessage() + ",input data: {}" + data + ", update fields: {}" + update);
            log.warn("update airport failed: {} [code 500]", e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @DeleteMapping("${mapping.airport.delete}/{id}")
    public ResponseEntity<Void> delete(@PathVariable("id") long id) {
        try {
            repo.deleteById(id);
            log.info("delete airport successful: id={} [code 200]", id);
            return ResponseEntity.ok().build();
        } catch (EmptyResultDataAccessException e) {
            log.warn("delete airport failed: id={} not exists [code 200]", id);
            return ResponseEntity.ok().build();
        } catch (Exception e) {
            log.debug("Error airport delete:{}" +  e.getMessage() + ",input parameters:id={}" + id);
            log.warn("delete airport failed: {} [code 500]", e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    private boolean containsNullFields(AirportModel data) {
        return data.getName() == null ||
                data.getX() == null ||
                data.getY() == null ||
                data.getSize() == null ||
                data.getName().isEmpty();
    }

}
