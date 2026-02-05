package com.gabrielodisi.contadorvoltas.model;

import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;
import lombok.Data;
import lombok.Getter;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

@Getter
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
    private int voltasConcluidas = 0;
    private LocalDate dataTreino = LocalDate.now();
    private Long tempo;
    private boolean concluido;

    @ElementCollection
    @CollectionTable(
            name = "treino_voltas",
            joinColumns = @JoinColumn(name = "treino_id")
    )
    @JsonIgnore
    private List<Volta> voltas = new ArrayList<>();

    public void adicionarVolta(Long tempoVolta) {
        if (this.concluido) {
            throw new IllegalStateException("Treino já foi concluído");
        }

        this.voltasConcluidas++;
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
                .mapToLong(Volta::getTempoVolta)
                .sum();
    }
}
