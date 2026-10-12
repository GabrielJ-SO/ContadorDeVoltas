package com.gabrielodisi.contadorvoltas.service;

import com.gabrielodisi.contadorvoltas.model.treinos.Tiro;
import com.gabrielodisi.contadorvoltas.model.treinos.TreinoIntervalado;
import com.gabrielodisi.contadorvoltas.repository.TreinoIntervaladoRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class TreinoIntervaladoService {

    @Autowired
    private TreinoIntervaladoRepository repository;

    public TreinoIntervalado iniciarTreino(TreinoIntervalado treinoIntervalado) { return repository.save(treinoIntervalado); }

    public List<Tiro> listarTiros(long id) {

        if (repository.findById(id).isPresent()) {
            return repository.listarTiros(id);
        }
        else {
            throw new RuntimeException("Treino não encontrado.");
        }
    }
}
