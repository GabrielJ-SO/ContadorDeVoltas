package com.gabrielodisi.contadorvoltas.model;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.gabrielodisi.contadorvoltas.model.treinos.Treino;
import jakarta.persistence.*;
import jakarta.validation.constraints.Size;
import lombok.Getter;

import java.util.List;

@Getter
@Entity
public class Atleta extends Pessoa {

    @Size(min = 24, max = 24)
    private String tagRFID;

    @OneToMany(mappedBy = "atleta", orphanRemoval = true, fetch = FetchType.EAGER)
    @JsonIgnore
    private List<Treino> treinos;

}
