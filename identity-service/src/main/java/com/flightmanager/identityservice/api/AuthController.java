package com.flightmanager.identityservice.api;

import com.flightmanager.identityservice.exception.HTTP400Exception;
import com.flightmanager.identityservice.models.AuthorizeRequest;
import com.flightmanager.identityservice.models.TokenRequest;
import com.flightmanager.identityservice.models.TokenResponse;
import com.flightmanager.identityservice.models.UserModel;
import com.flightmanager.identityservice.service.AuthService;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;


@RestController
public class AuthController {
    private final Logger log = LogManager.getLogger(AuthController.class);


    @Autowired
    private AuthService authService;

    @PostMapping("${mapping.auth.login}")
    public ResponseEntity<TokenResponse> login(@RequestBody TokenRequest tokenRequest) {
        try {
            if (tokenRequest == null ||
                    tokenRequest.getEmail() == null ||
                    tokenRequest.getEmail().isEmpty() ||
                    tokenRequest.getPassword() == null ||
                    tokenRequest.getPassword().isEmpty()
            ) {

                log.warn("login failed: invalid login data [code 400]");
                return ResponseEntity.status(400).build();
            }
            TokenResponse response = authService.login(tokenRequest.getEmail(), tokenRequest.getPassword());
            if (response == null) {
                log.warn("login failed: invalid login data [code 401]");
                return ResponseEntity.status(401).build();
            }
            log.info("login successful: id={} [code 200]", response.getId());
            return ResponseEntity.ok(response);
        } catch (Exception e) {
            log.debug("Error during login: {}"+ e.getMessage());
            log.warn("login failed: {} [code 500]", e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.auth.register}")
    public ResponseEntity<TokenResponse> register(@RequestBody UserModel data) {
        try {
            if (data.getEmail() == null || data.getEmail().isEmpty()) {
                log.warn("register failed: invalid register data [code 400]");
                return ResponseEntity.status(400).build();
            }
            TokenResponse response = authService.register(data);
            if (response == null) {
                log.warn("register failed: user already exists [code 409]");
                return ResponseEntity.status(409).build();
            }
            log.info("register successful: id={} [code 200]", response.getId());
            return ResponseEntity.ok(response);
        } catch (HTTP400Exception e) {
            log.debug("Error during registration: {}" + e.getMessage() + ", id={}");
            log.warn("register failed: invalid register data [code 400]");
            return ResponseEntity.status(400).build();
        } catch (Exception e) {
            log.debug("Error during registration: {}"+ e.getMessage());
            log.warn("register failed: {} [code 500]", e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.auth.authorize}")
    public ResponseEntity<Boolean> authorize(@RequestBody AuthorizeRequest authorizeRequest) {
        try {
            boolean authorize = authService.authorize(authorizeRequest.getToken(), authorizeRequest.getPermissions());
            log.debug("authorize successful: value=" + authorize + "permissions count=" + authorizeRequest.getPermissions().size());
            log.info("authorize successful: value={} [code 200]", authorize);
            return ResponseEntity.ok(authorize);
        } catch (Exception e) {
            log.debug("Error during authorization: {}"+ e.getMessage());
            log.warn("authorize failed: {} [code 500]", e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }

    @PostMapping("${mapping.auth.id-by-token}")
    public ResponseEntity<Long> getIdByToken(@RequestBody String token) {
        try {
            Long id = authService.getIdFromToken(token);
            if (id == null) {
                log.warn("id-by-token failed: invalid token or user not exists [code 401]");
                return ResponseEntity.status(401).build();
            }
            log.info("id-by-token successful: id={} [code 200]", id);
            return ResponseEntity.ok(id);
        } catch (Exception e) {
            log.debug("Error during id-by-token: {}" + e.getMessage());
            log.warn("id-by-token failed: {} [code 500]", e.getMessage());
            return ResponseEntity.status(500).build();
        }
    }


}
