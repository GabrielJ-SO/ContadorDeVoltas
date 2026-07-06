package com.gabrielodisi.contadorvoltas.model;

import jakarta.persistence.Embeddable;
import lombok.Data;

@Data
@Embeddable
public class Volta {

    private int numero;
    private long tempo;

    protected Volta() {}

    protected Volta(int numero, long tempo) {
        this.numero = numero;
        this.tempo = tempo;
    }
}
