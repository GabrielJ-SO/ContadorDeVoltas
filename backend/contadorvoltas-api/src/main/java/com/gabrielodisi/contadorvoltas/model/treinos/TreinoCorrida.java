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
    public boolean registrarVolta(long tempoVolta) {
        if (super.getEstado() != EstadoTreino.EM_ANDAMENTO) { return false; }

        int numeroVolta = getVoltas().size() + 1;
        getVoltas().add(new Volta(numeroVolta, tempoVolta));
        super.distanciaCorridaMetros += Volta.DISTANCIA_VOLTA_METROS;

        if (this.numeroVoltas == getVoltas().size()) { concluirTreino(); }

        return true;
    }

}
