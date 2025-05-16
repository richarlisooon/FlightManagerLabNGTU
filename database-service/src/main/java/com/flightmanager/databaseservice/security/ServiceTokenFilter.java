package com.flightmanager.databaseservice.security;

import com.flightmanager.databaseservice.config.PropertiesConfig;
import lombok.RequiredArgsConstructor;
import org.apache.log4j.LogManager;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Component;
import org.springframework.util.StringUtils;
import org.springframework.web.filter.GenericFilterBean;

import javax.servlet.FilterChain;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@Component
@RequiredArgsConstructor
public class ServiceTokenFilter extends GenericFilterBean {
    private final Logger log = LogManager.getLogger(ServiceTokenFilter.class);


    @Autowired
    private PropertiesConfig properties;
    @Autowired
    private ServiceAuthorizer authorizer;

    @Override
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain fc) {
        final String token = getTokenFromRequest((HttpServletRequest) request);
        try {
            if (token != null && authorizer.authorize(token)) {
                final ServiceAuthentication appInfoToken = new ServiceAuthentication();
                appInfoToken.setAuthenticated(true);
                appInfoToken.setServiceName("service");
                SecurityContextHolder.getContext().setAuthentication(appInfoToken);
            }
        } catch (Exception e) {
            log.debug("Error during ServiceTokenFilter doFilter:{}" + e.getMessage());
            log.warn(e.getMessage());
        }
        try {
            fc.doFilter(request, response);
        } catch (Exception e) {
            log.debug("Error during ServiceTokenFilter doFilter:{}" + e.getMessage() + ", request={}" + request + ", response={}"+response);
            log.warn(e.getMessage());
            ((HttpServletResponse) response).setStatus(400);
        }
    }

    private String getTokenFromRequest(HttpServletRequest request) {
        final String token = request.getHeader(properties.getServiceTokenHeader());
        if (StringUtils.hasText(token)) {
            return token;
        }
        return null;
    }

}
