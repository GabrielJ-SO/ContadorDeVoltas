package com.gabrielodisi.contadorvoltas.model;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

@Getter
@Entity
@Inheritance(strategy = InheritanceType.JOINED)
abstract public class Treino {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ElementCollection
    @CollectionTable(name = "treino_voltas", joinColumns = @JoinColumn(name = "treino_id"))
    private List<Volta> voltas = new ArrayList<>();

    @ManyToOne(optional = false)
    @JoinColumn(name = "atleta_id")
    Atleta atleta;

    private String nome;
    private LocalDate data = LocalDate.now();
    private boolean concluido;
    @Setter
    private boolean publico;

    public abstract void registrarVolta(long tempoVolta);
    public abstract long getTempoTotal();
    public abstract boolean isConcluido();

    protected void concluirTreino() {
        this.concluido = true;
    }

    public int getNumeroVoltasConcluidas() {
        return this.voltas.size();
    }

}
