package com.gabrielodisi.contadorvoltas.model;

import jakarta.persistence.Embeddable;
import lombok.Getter;

@Getter
@Embeddable
public class Volta {

    private int numeroVolta;
    private Long tempoVolta;

    protected Volta() {
        // JPA
    }

    public Volta(int numeroVolta, Long tempoVolta) {
        this.numeroVolta = numeroVolta;
        this.tempoVolta = tempoVolta;
    }

}
