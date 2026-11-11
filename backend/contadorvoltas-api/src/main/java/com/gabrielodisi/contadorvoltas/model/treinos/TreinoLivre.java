package com.gabrielodisi.contadorvoltas.model.treinos;

import jakarta.persistence.Entity;

@Entity
public class TreinoLivre extends Treino {

    @Override
    public boolean registrarVolta(long tempoVolta) {
        if (super.getEstado() != EstadoTreino.EM_ANDAMENTO) { return false;}

        int numeroVolta = getVoltas().size() + 1;
        getVoltas().add(new Volta(numeroVolta, tempoVolta));
        super.distanciaCorridaMetros += Volta.DISTANCIA_VOLTA_METROS;

        return true;
    }

    @Override
    public void finalizarTreino() { this.setEstado(EstadoTreino.CONCLUIDO); }
}
