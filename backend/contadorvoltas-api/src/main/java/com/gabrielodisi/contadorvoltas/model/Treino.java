package com.gabrielodisi.contadorvoltas.model;

import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

@NoArgsConstructor
@Entity
@Inheritance(strategy = InheritanceType.JOINED)
abstract public class Treino {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

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

    @ElementCollection
    @CollectionTable(
            name = "treino_voltas",
            joinColumns = @JoinColumn(name = "treino_id")
    )
    @JsonIgnore
    @Getter
    private List<Volta> voltas = new ArrayList<>();

    @Getter
    @NoArgsConstructor
    @Embeddable
    public static class Volta {
        private int numero;
        private long tempo;

        protected Volta(int numero, long tempo) {
            this.numero = numero;
            this.tempo = tempo;
        }
    }

}
