package com.gabrielodisi.contadorvoltas.model;

import jakarta.persistence.Entity;

@Entity
public class TreinoCorrida extends Treino {

    private int numeroVoltas;


    @Override
    protected void registrarVolta(long tempoVolta) {

    }

    @Override
    public long getTempoTotal() {
        return 0;
    }
}
