package com.gabrielodisi.contadorvoltas.model.treinos;

import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

import java.util.ArrayList;
import java.util.List;

@Getter
@Setter
@Entity
public class TreinoIntervalado extends Treino {

    private int numeroTiros;
    private int numeroVoltas;
    private long tempoDescanso;

    @OneToMany(mappedBy = "treinoIntervalado", cascade = CascadeType.ALL, orphanRemoval = true, fetch = FetchType.EAGER)
    @JsonIgnore
    private List<Tiro> tiros = new ArrayList<>();


    private void registrarVoltaTiros(long tempoVolta) {
        if (tiros.isEmpty()) {
            tiros.add(new Tiro(1, numeroVoltas, this));
            tiros.getLast().registrarVolta(tempoVolta);
        }
        else if (!(tiros.getLast().isConcluido())) {
            tiros.getLast().registrarVolta(tempoVolta);
        }
        else {
            tiros.add(new Tiro(tiros.size() + 1, numeroVoltas, this));
            tiros.getLast().registrarVolta(tempoVolta);
        }

    }

    @Override
    public void registrarVolta(long tempoVolta) {
        if (!isConcluido()) {
            registrarVoltaTiros(tempoVolta);

            int numero = getVoltas().size() + 1;
            getVoltas().add(new Volta(numero,  tempoVolta));
            super.distanciaCorridaMetros += Volta.DISTANCIA_VOLTA_METROS;
        }

        if (isConcluido()) { concluirTreino(); }
    }


    public boolean isConcluido() { return numeroTiros == tiros.size() && tiros.getLast().isConcluido(); }

}
