package com.gabrielodisi.contadorvoltas.model;

import jakarta.persistence.Entity;

@Entity
public class TreinoLivre extends Treino {

    public int getNumeroVoltas() {
        return 0;
    }

    @Override
    protected void registrarVolta(long tempoVolta) {

    }

    @Override
    public long getTempoTotal() {
        return 0;
    }
}
