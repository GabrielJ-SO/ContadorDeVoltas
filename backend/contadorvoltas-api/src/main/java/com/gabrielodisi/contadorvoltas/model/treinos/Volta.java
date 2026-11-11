package com.gabrielodisi.contadorvoltas.model.treinos;

import jakarta.persistence.Embeddable;
import lombok.Data;

@Data
@Embeddable
public class Volta {

    public static final int DISTANCIA_VOLTA_METROS = 150;

    private int numero;
    private long tempo;

    protected Volta() {}

    protected Volta(int numero, long tempo) {
        this.numero = numero;
        this.tempo = tempo;
    }
}
