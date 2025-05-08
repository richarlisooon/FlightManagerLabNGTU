package com.flightmanager.identityservice.config;

import com.flightmanager.identityservice.security.HttpHeaderInterceptor;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.http.client.ClientHttpResponse;
import org.springframework.web.client.ResponseErrorHandler;
import org.springframework.web.client.RestTemplate;

import java.util.Collections;

@Configuration
public class ServiceConfig {


    @Bean
    public RestTemplate restTemplate() {
        RestTemplate restTemplate = new RestTemplate();
        restTemplate.setInterceptors(Collections.singletonList(headerRequestInterceptor()));
        restTemplate.setErrorHandler(new ResponseErrorHandler() {
            @Override
            public boolean hasError(ClientHttpResponse response) {
                return false;
            }

            @Override
            public void handleError(ClientHttpResponse response) {

            }
        });
        return restTemplate;
    }

    @Bean
    public HttpHeaderInterceptor headerRequestInterceptor() {
        return new HttpHeaderInterceptor();
    }
}
