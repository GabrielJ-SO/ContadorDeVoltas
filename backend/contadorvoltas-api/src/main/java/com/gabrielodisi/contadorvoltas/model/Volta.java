package com.gabrielodisi.contadorvoltas.model;

import jakarta.persistence.Embeddable;
import lombok.Getter;

import java.time.LocalTime;
@Getter
@Embeddable
public class Volta {

    private int numeroVolta;
    private LocalTime tempoVolta;

    protected Volta() {
        // JPA
    }

    public Volta(int numeroVolta, LocalTime tempoVolta) {
        this.numeroVolta = numeroVolta;
        this.tempoVolta = tempoVolta;
    }

}
