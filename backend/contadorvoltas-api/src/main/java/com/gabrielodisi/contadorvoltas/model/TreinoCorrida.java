package com.gabrielodisi.contadorvoltas.model;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

@Entity
public class TreinoCorrida extends Treino {

    @Setter
    @Getter
    private int numeroVoltas;

    @Override
    public void registrarVolta(long tempoVolta) {
        if (isConcluido()) { throw new IllegalStateException("Treino já foi concluído"); }

        int numeroVolta = getVoltas().size() + 1;
        getVoltas().add(new Volta(numeroVolta, tempoVolta));

        if (isConcluido()) { concluirTreino(); }
    }

    @Override
    public long getTempoTotal() {
        return getVoltas().stream()
                .mapToLong(Volta::getTempo)
                .sum();
    }

    @Override
    public boolean isConcluido() {
        return numeroVoltas == getVoltas().size();
    }

}
