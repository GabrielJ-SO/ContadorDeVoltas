package com.gabrielodisi.contadorvoltas.service;

import com.gabrielodisi.contadorvoltas.model.treinos.EstadoTreino;
import com.gabrielodisi.contadorvoltas.model.treinos.Treino;
import com.gabrielodisi.contadorvoltas.model.treinos.Volta;
import com.gabrielodisi.contadorvoltas.repository.TreinoRepository;
import jakarta.persistence.EntityNotFoundException;
import jakarta.transaction.Transactional;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class TreinoService {

    @Autowired
    private TreinoRepository repository;

    public List<Treino> listar() { return repository.findAll(); }

    public Optional<Treino> buscarPorId(Long id) { return repository.findById(id); }


    public void iniciarTreino(long id) {
        Treino treino = repository.findById(id)
                .orElseThrow(() -> new EntityNotFoundException("Treino não encontrado."));

        if (treino.getEstado() == EstadoTreino.NAO_INICIADO) {
            treino.setEstado(EstadoTreino.EM_ANDAMENTO);
        }
    }

    public void finalizarTreino(long id) {
        Treino treino = repository.findById(id)
                .orElseThrow(() -> new EntityNotFoundException("Treino não encontrado."));

        treino.finalizarTreino();
    }

    public void deletar(Long id) {
        if (repository.existsById(id)) {
            repository.deleteById(id);
        }
        else {
            throw new RuntimeException("Treino não encontrado");
        }
    }

    public List<Volta> buscarVoltas(Long id){
        Treino treino = repository.findById(id)
                .orElseThrow(() -> new EntityNotFoundException("Treino não encontrado."));

        return treino.getVoltas();
    }

    @Transactional
    public void registrarVolta(Long id, Long tempoVolta) {
        Treino treino = repository.findById(id)
                .orElseThrow(() -> new EntityNotFoundException("Treino não encontrado para registrar volta."));

        treino.registrarVolta(tempoVolta);
    }

}
