package com.gabrielodisi.contadorvoltas.service;

import com.gabrielodisi.contadorvoltas.model.Treino;
import com.gabrielodisi.contadorvoltas.model.Volta;
import com.gabrielodisi.contadorvoltas.repository.TreinoRepository;
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

    public List<Volta> listarVoltas(Long treinoId) {
        Optional<Treino> treino = repository.findById(treinoId);
        if (treino.isPresent()) {
            return treino.get().getVoltas();
        }
        else {
            throw new RuntimeException("Treino não encontrado");
        }
    }

}
