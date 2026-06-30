package com.gabrielodisi.contadorvoltas.model;

import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;
import lombok.Getter;
import lombok.NoArgsConstructor;

import java.util.ArrayList;
import java.util.List;

@Entity
public class TreinoIntervalado extends Treino {

    private int numeroRepeticoes;
    private int numeroVoltas;
    private long tempoDescanso;

    @ElementCollection
    @CollectionTable(
            name = "repeticoes_intervalado",
            joinColumns = @JoinColumn(name = "treino_id")
    )
    @JsonIgnore
    @Getter
    private List<Repeticao> repeticoes = new ArrayList<>();

    private void registrarVoltaRepeticao(long tempoVolta) {
        if (!repeticoes.isEmpty()) {
            if (!repeticoes.getLast().concluido) {
                Repeticao r = repeticoes.getLast();
                r.registrarVolta(numeroVoltas, tempoVolta);
            }
            else {
                int numero = repeticoes.size() + 1;
                repeticoes.add(new Repeticao(numero));
            }
        }
        else {
            repeticoes.add(new Repeticao(1));
        }
    }

    @Override
    public void registrarVolta(long tempoVolta) {
        if (!isConcluido()) {
            registrarVoltaRepeticao(tempoVolta);

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
        return numeroRepeticoes == repeticoes.size();
    }


    @Getter
    @NoArgsConstructor
    @Embeddable
    private static class Repeticao {
        private int numero;
        private boolean concluido;
        private List<Volta> voltas = new ArrayList<>();

        public Repeticao(int numero) {
            this.numero = numero;
        }

        protected void registrarVolta(int numeroVoltas, long tempoVolta) {
            this.voltas.add(new Volta(voltas.size() + 1, tempoVolta));

            if (numeroVoltas >= this.voltas.size()) {
                this.concluido = true;
            }
        }

        protected long calcularTempo() {
            return getVoltas().stream()
                    .mapToLong(Volta::getTempo)
                    .sum();
        }

    }

}
