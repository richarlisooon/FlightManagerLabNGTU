package com.flightmanager.identityservice.jwt;

import com.flightmanager.identityservice.config.PropertiesConfig;
import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;
import io.jsonwebtoken.io.Decoders;
import io.jsonwebtoken.security.Keys;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.stereotype.Service;

import java.security.Key;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

@Service
public class JwtUtil {
    private final Logger log = LogManager.getLogger(JwtUtil.class);

    @Autowired
    private PropertiesConfig properties;

    public String generateToken(UserDetails userDetails) {
        Map<String, Object> claims = new HashMap<>();
        if (userDetails instanceof UserAuth) {
            claims.put("id", ((UserAuth) userDetails).getId());
            claims.put("email", ((UserAuth) userDetails).getEmail());
            claims.put("roles", ((UserAuth) userDetails).getRoles());
        }
        log.debug("User details for token generation: ID={}, Email={}, Roles={}",
                claims.get("id"), claims.get("email"), claims.get("roles"));
        return generateToken(claims, userDetails);
    }

    private String generateToken(Map<String, Object> extraClaims, UserDetails userDetails) {
        String subject = userDetails.getUsername();

        log.debug("Creating token for subject: {}" + subject);

        return Jwts.builder().setClaims(extraClaims).setSubject(userDetails.getUsername())
                .setIssuedAt(new Date(System.currentTimeMillis()))
                .setExpiration(new Date(System.currentTimeMillis() + 100000 * 60 * 24))
                .signWith(getSigningKey(), SignatureAlgorithm.HS256).compact();
    }

    public boolean isTokenExpired(String token) {
        try {
            boolean expired = extractAllClaims(token).getExpiration().before(new Date());
            log.debug("Token expiration status: {}", expired ? "Expired" : "Valid");
            return extractAllClaims(token).getExpiration().before(new Date());
        } catch (NullPointerException e) {
            log.debug("Error while checking token expiration", e);

            return false;
        }
    }

    public String extractId(String token) {
        try {
            String id = extractAllClaims(token).get("id").toString();
            log.debug("Extracted ID from token: {}", id);
            return extractAllClaims(token).get("id").toString();
        } catch (NullPointerException e) {
            log.debug("Error extracting ID from token", e);
            return null;
        }
    }

    private Claims extractAllClaims(String token) {
        try {

            return Jwts.parser().setSigningKey(getSigningKey()).parseClaimsJws(token)
                    .getBody();
        } catch (Exception e) {
            log.error("Error extracting claims from token", e);

            return null;
        }
    }

    private Key getSigningKey() {
        byte[] keyBytes = Decoders.BASE64.decode(properties.getJwtSecret());
        return Keys.hmacShaKeyFor(keyBytes);
    }
}
