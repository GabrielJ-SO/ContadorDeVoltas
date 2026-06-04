package com.gabrielodisi.contadorvoltas.model;

import jakarta.persistence.Entity;

@Entity
public class TreinoIntervalado extends Treino {

    private int numeroRepeticoes;
    private int numeroVoltas;
    private long tempoDescanco;


    @Override
    protected void registrarVolta(long tempoVolta) {

    }

    @Override
    public long getTempoTotal() {
        return 0;
    }
}
