package com.gabrielodisi.contadorvoltas.model.treinos;

import com.gabrielodisi.contadorvoltas.model.Atleta;
import jakarta.persistence.*;
import lombok.Data;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

@Data
@Entity
@Inheritance(strategy = InheritanceType.JOINED)
abstract public class Treino {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ElementCollection(fetch = FetchType.EAGER)
    @CollectionTable(name = "treino_voltas", joinColumns = @JoinColumn(name = "treino_id"))
    private List<Volta> voltas = new ArrayList<>();

    @ManyToOne(optional = false)
    @JoinColumn(name = "atleta_id")
    Atleta atleta;

    private String nome;
    private LocalDate data = LocalDate.now();
    private EstadoTreino estado = EstadoTreino.NAO_INICIADO;
    protected int distanciaCorridaMetros = 0;

    public abstract void registrarVolta(long tempoVolta);

    public void finalizarTreino() {
        if (this.getEstado() != EstadoTreino.CONCLUIDO) {
            this.setEstado(EstadoTreino.INCOMPLETO);
        }
    }

    public long getTempoTotalMS() {
        return getVoltas().stream()
              .mapToLong(Volta::getTempo)
              .sum();
    }

    public void concluirTreino() {
        this.estado = EstadoTreino.CONCLUIDO;
    }

    public int getNumeroVoltasConcluidas() {
        return this.voltas.size();
    }

}
