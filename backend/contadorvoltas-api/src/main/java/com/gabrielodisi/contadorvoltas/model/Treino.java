package com.gabrielodisi.contadorvoltas.model;


import jakarta.persistence.*;
import lombok.Data;

import java.time.Duration;
import java.time.LocalDate;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.List;

@Data
@Entity
public class Treino {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToOne(optional = false)
    @JoinColumn(name = "atleta_id")
    private Atleta atleta;

    private int totalVoltas;
    private String nome;
    private LocalDate dataTreino;
    private Duration tempo;
    private boolean concluido;

    @ElementCollection
    @CollectionTable(
            name = "treino_voltas",
            joinColumns = @JoinColumn(name = "treino_id")
    )
    private List<Volta> voltas = new ArrayList<>();


    public void adicionarVolta(LocalTime tempoVolta) {
        if (this.concluido) {
            throw new IllegalStateException("Treino já foi concluído");
        }

        int numero = voltas.size() + 1;
        voltas.add(new Volta(numero, tempoVolta));

        recalcularTempoTotal();

        if (numero == this.totalVoltas) {
            concluirTreino();
        }
    }

    public void concluirTreino() {
        this.concluido = true;
    }

    private void recalcularTempoTotal() {
        this.tempo = voltas.stream()
                .map(v -> Duration.between(LocalTime.MIDNIGHT, v.getTempoVolta()))
                .reduce(Duration.ZERO, Duration::plus);
    }
}
