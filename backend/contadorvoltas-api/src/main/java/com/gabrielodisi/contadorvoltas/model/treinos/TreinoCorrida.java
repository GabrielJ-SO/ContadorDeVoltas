package com.gabrielodisi.contadorvoltas.model.treinos;

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
        if (super.getEstado() == EstadoTreino.CONCLUIDO) { throw new IllegalStateException("Treino já foi concluído"); }

        int numeroVolta = getVoltas().size() + 1;
        getVoltas().add(new Volta(numeroVolta, tempoVolta));
        super.distanciaCorridaMetros += Volta.DISTANCIA_VOLTA_METROS;

        if (this.numeroVoltas == getVoltas().size()) { concluirTreino(); }
    }

    @Override
    public void finalizarTreino() {
        if (this.getEstado() != EstadoTreino.CONCLUIDO) {
            this.setEstado(EstadoTreino.INCOMPLETO);
        }
    }

}
