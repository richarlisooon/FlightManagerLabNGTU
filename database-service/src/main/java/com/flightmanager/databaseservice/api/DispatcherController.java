package com.flightmanager.databaseservice.api;

import com.flightmanager.databaseservice.models.DispatcherModel;
import com.flightmanager.databaseservice.models.RoleModel;
import com.flightmanager.databaseservice.repos.DispatcherRepo;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.stream.Collectors;


@RestController
public class DispatcherController {
    private final Logger log = LogManager.getLogger(DispatcherController.class);

    @Autowired
    private DispatcherRepo repo;


    @GetMapping("${mapping.dispatcher.get}")
    public ResponseEntity<List<DispatcherModel>> get(
            @RequestParam(value = "id", required = false) Long id,
            @RequestParam(value = "firstName", required = false) String firstName,
            @RequestParam(value = "lastName", required = false) String lastName,
            @RequestParam(value = "email", required = false) String email,
            @RequestParam(value = "password", required = false) String password,
            @RequestParam(value = "isBanned", required = false) Boolean isBanned,
            @RequestParam(value = "roles", required = false) String roles
    ) {
        try {
            List<DispatcherModel> models = repo.findAll();
            if (id != null)
                models = models.stream().filter(m -> m.getId().equals(id)).collect(Collectors.toList());
            if (firstName != null)
                models = models.stream().filter(m -> m.getFirstName().equals(firstName)).collect(Collectors.toList());
            if (lastName != null)
                models = models.stream().filter(m -> m.getLastName().equals(lastName)).collect(Collectors.toList());
            if (email != null)
                models = models.stream().filter(m -> m.getEmail().equals(email)).collect(Collectors.toList());
            if (password != null)
                models = models.stream().filter(m -> m.getPassword().equals(password)).collect(Collectors.toList());
            if (isBanned != null)
                models = models.stream().filter(m -> m.getIsBanned().equals(isBanned)).collect(Collectors.toList());
            if (roles != null && !roles.isEmpty()) {
                HashSet<RoleModel> rolesSet = new HashSet<>();
                for (String role : roles.split(",")) {
                    final boolean[] fl = {false};
                    Arrays.stream(RoleModel.values()).forEach(roleModel -> {
                        if (role.equals(roleModel.name()))
                            fl[0] = true;
                    });
                    if (!fl[0]) {
                        log.warn("get dispatcher failed: wrong roles [code 400]");
                        return ResponseEntity.status(400).build();
                    }
                    rolesSet.add(RoleModel.valueOf(role));
                }
                models = models.stream().filter(m -> m.getRoles().containsAll(rolesSet) && rolesSet.containsAll(m.getRoles())).collect(Collectors.toList());
            }
            log.info("get dispatcher successful ({} entities) [code 200]", models.size());
            return ResponseEntity.ok(models);
        } catch (Exception e) {
            log.debug("Error get dispatcher retrial:{}" + e.getMessage()+ ",input parameters:id={}" + id + ", firstName={}" + firstName + ", email={}" + email + ", password={}" + password + ", isBanned={}" + isBanned + ", roles={}" + roles);
            log.warn("get dispatcher failed: {} [code 500]", e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.dispatcher.create}")
    public ResponseEntity<DispatcherModel> create(@RequestBody DispatcherModel data) {
        try {
            data.setId(0L);
            if (containsNullFields(data)) {
                log.warn("create dispatcher failed: invalid data [code 400]");
                return ResponseEntity.status(400).build();
            }
            DispatcherModel model = repo.save(data);
            log.info("create dispatcher successful: id={} [code 200]", model.getId());
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            log.debug("Error creating dispatcher:{}" + e.getMessage() + ",input data={}"+ data);
            log.warn("create dispatcher failed: {} [code 500]", e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.dispatcher.update}")
    public ResponseEntity<DispatcherModel> update(@RequestBody DispatcherModel data, @RequestParam("update") String update) {
        try {
            if (data.getId() == null) {
                log.warn("update dispatcher failed: id not provided [code 400]");
                return ResponseEntity.status(400).build();
            }
            DispatcherModel fromDB = repo.findById(data.getId()).orElse(null);
            if (fromDB == null) {
                log.warn("update dispatcher failed: dispatcher not found [code 400]");
                return ResponseEntity.status(400).build();
            }

            ArrayList<String> fields = new ArrayList<>(Arrays.asList(update.split(",")));
            if (!fields.contains("firstName"))
                data.setFirstName(fromDB.getFirstName());
            if (!fields.contains("lastName"))
                data.setLastName(fromDB.getLastName());
            if (!fields.contains("email"))
                data.setEmail(fromDB.getEmail());
            if (!fields.contains("password"))
                data.setPassword(fromDB.getPassword());
            if (!fields.contains("isBanned"))
                data.setIsBanned(fromDB.getIsBanned());
            if (!fields.contains("roles"))
                data.setRoles(fromDB.getRoles());
            if (containsNullFields(data)) {
                log.warn("update dispatcher failed: invalid data [code 400]");
                return ResponseEntity.status(400).build();
            }

            DispatcherModel model = repo.save(data);
            log.info("update dispatcher successful: id={} [code 200]", model.getId());
            return ResponseEntity.ok(model);
        } catch (Exception e) {
            log.debug("Error dispatcher update:{}" + e.getMessage() + ",input data: {}" + data + ", update fields: {}" + update);
            log.warn("update dispatcher failed: {} [code 500]", e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @DeleteMapping("${mapping.dispatcher.delete}/{id}")
    public ResponseEntity<Void> delete(@PathVariable("id") long id) {
        try {
            repo.deleteById(id);
            log.info("delete dispatcher successful: id={} [code 200]", id);
            return ResponseEntity.ok().build();
        } catch (EmptyResultDataAccessException e) {
            log.warn("delete dispatcher failed: id={} not exists [code 200]", id);
            return ResponseEntity.ok().build();
        } catch (Exception e) {
            log.debug("Error dispatcher delete:{}" +  e.getMessage() + ",input parameters:id={}" + id);
            log.warn("delete dispatcher failed: {} [code 500]", e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    private boolean containsNullFields(DispatcherModel data) {
        return data.getFirstName() == null ||
                data.getLastName() == null ||
                data.getEmail() == null ||
                data.getPassword() == null ||
                data.getIsBanned() == null ||
                data.getRoles() == null ||
                data.getFirstName().isEmpty() ||
                data.getLastName().isEmpty() ||
                data.getEmail().isEmpty() ||
                data.getPassword().isEmpty();
    }

}
