package com.gabrielodisi.contadorvoltas.service;

import com.gabrielodisi.contadorvoltas.model.Treino;
import com.gabrielodisi.contadorvoltas.model.Volta;
import com.gabrielodisi.contadorvoltas.repository.TreinoRepository;
import jakarta.persistence.EntityNotFoundException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class TreinoService {

    @Autowired
    private TreinoRepository repository;

    public List<Treino> listar() { return repository.findAll(); }

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

}
