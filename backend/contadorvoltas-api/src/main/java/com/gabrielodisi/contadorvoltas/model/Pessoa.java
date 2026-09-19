package com.gabrielodisi.contadorvoltas.model;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;
import org.hibernate.validator.constraints.UniqueElements;

@MappedSuperclass
abstract public class Pessoa {

    @Getter
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Getter
    @Column(unique = true)
    private String nome;

    @Setter
    private String senha;

}
