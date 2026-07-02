package com.gabrielodisi.contadorvoltas.model;

import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;
import lombok.Getter;

import java.util.ArrayList;
import java.util.List;

@Getter
@Entity
public class TreinoIntervalado extends Treino {

    private int numeroTiros;
    private int numeroVoltas;
    private long tempoDescanso;

    @OneToMany(mappedBy = "treinoIntervalado", cascade = CascadeType.ALL, orphanRemoval = true, fetch = FetchType.EAGER)
    @JsonIgnore
    private List<Tiro> tiros = new ArrayList<>();


    private void registrarVoltaTiros(long tempoVolta) {
        if (!tiros.isEmpty()) {
            if (!tiros.getLast().isConcluido()) {
                Tiro t = tiros.getLast();
                t.registrarVolta(numeroVoltas, tempoVolta);
            }
            else {
                int numero = tiros.size() + 1;
                tiros.add(new Tiro(numero));
            }
        }
        else {
            tiros.add(new Tiro(1));
        }
    }

    @Override
    public void registrarVolta(long tempoVolta) {
        if (!isConcluido()) {
            registrarVoltaTiros(tempoVolta);

            int numero = getVoltas().size() + 1;
            getVoltas().add(new Volta(numero,  tempoVolta));
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
        return numeroTiros == tiros.size();
    }

}
