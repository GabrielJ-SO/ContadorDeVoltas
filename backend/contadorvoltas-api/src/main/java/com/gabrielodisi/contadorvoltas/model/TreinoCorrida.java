package com.gabrielodisi.contadorvoltas.model;

import jakarta.persistence.*;

@Entity
public class TreinoCorrida extends Treino {

    private int numeroVoltas;

    @Override
    public void registrarVolta(long tempoVolta) {
        if (isConcluido()) {
            int numeroVolta = getVoltas().size() + 1;
            getVoltas().add(new Volta(numeroVolta, tempoVolta));
        }
        else {
            concluirTreino();
        }
    }

    @Override
    public long getTempoTotal() {
        return getVoltas().stream()
                .mapToLong(Volta::getTempo)
                .sum();
    }

    @Override
    public boolean isConcluido() {
        return numeroVoltas >= getVoltas().size();
    }

}
