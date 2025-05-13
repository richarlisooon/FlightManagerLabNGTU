package com.flightmanager.identityservice.security;

import com.flightmanager.identityservice.config.PropertiesConfig;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpRequest;
import org.springframework.http.client.ClientHttpRequestExecution;
import org.springframework.http.client.ClientHttpRequestInterceptor;
import org.springframework.http.client.ClientHttpResponse;
import org.springframework.stereotype.Component;

import java.io.IOException;

@Component
public class HttpHeaderInterceptor implements ClientHttpRequestInterceptor {

    @Autowired
    private PropertiesConfig properties;

    @Override
    public ClientHttpResponse intercept(HttpRequest request, byte[] body, ClientHttpRequestExecution execution) throws IOException {
        request.getHeaders().set(properties.getServiceTokenHeader(), properties.getServiceToken());
        return execution.execute(request, body);
    }
}
