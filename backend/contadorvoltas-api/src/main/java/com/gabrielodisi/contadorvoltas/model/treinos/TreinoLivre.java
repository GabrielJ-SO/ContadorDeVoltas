package com.gabrielodisi.contadorvoltas.model.treinos;

import jakarta.persistence.Entity;

@Entity
public class TreinoLivre extends Treino {

    @Override
    public void registrarVolta(long tempoVolta) {
        int numeroVolta = getVoltas().size() + 1;
        getVoltas().add(new Volta(numeroVolta, tempoVolta));
        super.distanciaCorridaMetros += Volta.DISTANCIA_VOLTA_METROS;
    }

    @Override
    public void finalizarTreino() { this.setEstado(EstadoTreino.CONCLUIDO); }
}
