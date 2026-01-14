package com.gabrielodisi.contadorvoltas.model;

import jakarta.persistence.*;
import jakarta.persistence.GenerationType;
import lombok.Data;

import java.util.ArrayList;
import java.util.List;

@Data
@Entity
public class Atleta {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)

    private Long id;
    private String nome;

    @OneToMany(mappedBy = "atleta", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<Treino> treinos = new ArrayList<>();
}
