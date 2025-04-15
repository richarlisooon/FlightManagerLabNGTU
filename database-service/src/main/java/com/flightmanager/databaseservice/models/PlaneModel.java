package com.flightmanager.databaseservice.models;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import javax.persistence.*;

@Entity
@Table(name = "planes")
@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
public class PlaneModel {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String name;
    private String pilot;
    private Integer builtYear;
    private Integer brokenPercentage;
    private Integer speed;
    private Integer minAirportSize;
}
