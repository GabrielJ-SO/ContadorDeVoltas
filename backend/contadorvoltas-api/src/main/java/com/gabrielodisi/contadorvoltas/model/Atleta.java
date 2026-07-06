package com.gabrielodisi.contadorvoltas.model;

import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;
import lombok.Getter;

import java.util.List;

@Getter
@Entity
public class Atleta extends Pessoa {

    @OneToMany(mappedBy = "atleta", cascade = CascadeType.ALL, orphanRemoval = true, fetch = FetchType.EAGER)
    @JsonIgnore
    private List<Treino> treinos;

}
