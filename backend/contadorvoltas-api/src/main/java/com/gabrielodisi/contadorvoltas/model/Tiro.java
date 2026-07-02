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
    private boolean concluido;

    @ElementCollection
    @CollectionTable(name = "repeticao_voltas", joinColumns = @JoinColumn(name = "treino_id"))
    private List<Volta> voltas = new ArrayList<>();

    public Tiro(int numero) {
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
