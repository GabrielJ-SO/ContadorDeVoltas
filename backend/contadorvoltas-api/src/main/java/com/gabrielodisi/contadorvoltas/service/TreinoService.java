package com.gabrielodisi.contadorvoltas.service;

import com.gabrielodisi.contadorvoltas.model.Treino;
import com.gabrielodisi.contadorvoltas.model.Volta;
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

    public Treino salvar(Treino treino) { return repository.save(treino); }

    public void deletar(Long id) {
        if (repository.existsById(id)) {
            repository.deleteById(id);
        }
        else {
            throw new RuntimeException("Treino não encontrado");
        }
    }

    @Transactional
    public void registrarVolta(Long treinoId, Long tempoVolta) {
        Treino treino = repository.findById(treinoId)
                .orElseThrow(() -> new EntityNotFoundException("Treino não encontrado"));

        treino.adicionarVolta(tempoVolta);
    }

    public List<Volta> listarVoltas(Long treinoId) {
        Optional<Treino> treino = repository.findById(treinoId);
        if (treino.isPresent()) {
            return repository.listarVoltas(treinoId);
        }
        else {
            throw new RuntimeException("Treino não encontrado");
        }
    }



}
