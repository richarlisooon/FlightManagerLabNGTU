package com.flightmanager.databaseservice.models;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import javax.persistence.*;
import java.util.Set;

@Entity
@Table(name = "dispatchers")
@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
public class DispatcherModel {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String firstName;
    private String lastName;
    private String email;
    private String password;
    private Boolean isBanned;
    @ElementCollection
    private Set<RoleModel> roles;
}
