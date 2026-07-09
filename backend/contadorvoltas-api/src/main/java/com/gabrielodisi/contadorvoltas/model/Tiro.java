package com.gabrielodisi.contadorvoltas.model;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.NoArgsConstructor;

import java.util.ArrayList;
import java.util.List;

@Getter
@Entity
@NoArgsConstructor
public class Tiro {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToOne(optional = false)
    @JoinColumn(name = "treino_id")
    TreinoIntervalado treinoIntervalado;

    private int numero;
    private int numeroVoltas;

    @ElementCollection(fetch = FetchType.EAGER)
    @CollectionTable(name = "tiro_voltas", joinColumns = @JoinColumn(name = "tiro_id"))
    private List<Volta> voltas = new ArrayList<>();

    public Tiro(int numero, int numeroVoltas, TreinoIntervalado treinoIntervalado) {
        this.numero = numero;
        this.numeroVoltas = numeroVoltas;
        this.treinoIntervalado = treinoIntervalado;
    }

    protected void registrarVolta(long tempoVolta) {
        if (!isConcluido()) {
            this.voltas.add(new Volta(voltas.size() + 1, tempoVolta));
        }
    }

    protected long calcularTempo() {
        return getVoltas().stream()
                .mapToLong(Volta::getTempo)
                .sum();
    }

    public boolean isConcluido() {
        return voltas.size() == numeroVoltas;
    }

}
