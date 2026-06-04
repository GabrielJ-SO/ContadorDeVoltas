package com.gabrielodisi.contadorvoltas.model;

import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

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
    private LocalDate data;
    private boolean concluido;
    private boolean publico;

    protected abstract void registrarVolta(long tempoVolta);
    public abstract long getTempoTotal();

    @ElementCollection
    @CollectionTable(
            name = "treino_voltas",
            joinColumns = @JoinColumn(name = "treino_id")
    )
    @JsonIgnore
    private List<Volta> voltas = new ArrayList<>();

    @Embeddable
    public class Volta {

        private int numero;
        private long tempo;

        protected Volta(int numero, long tempo) {
            this.numero = numero;
            this.tempo = tempo;
        }

        public Volta() {}


    }
}
