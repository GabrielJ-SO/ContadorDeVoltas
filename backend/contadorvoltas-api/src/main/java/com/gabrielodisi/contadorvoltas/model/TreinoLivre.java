package com.gabrielodisi.contadorvoltas.model;

import jakarta.persistence.Entity;

@Entity
public class TreinoLivre extends Treino {

    @Override
    public void registrarVolta(long tempoVolta) {
        int numeroVolta = getVoltas().size() + 1;
        getVoltas().add(new Volta(numeroVolta, tempoVolta));
    }

    @Override
    public long getTempoTotal() {
        return getVoltas().stream()
                .mapToLong(Volta::getTempo)
                .sum();
    }

    @Override
    public boolean isConcluido() {
        return true;
    }
}
