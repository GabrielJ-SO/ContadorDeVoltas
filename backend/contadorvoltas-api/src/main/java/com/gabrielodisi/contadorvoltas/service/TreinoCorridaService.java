package com.gabrielodisi.contadorvoltas.service;

import com.gabrielodisi.contadorvoltas.model.Treino;
import com.gabrielodisi.contadorvoltas.model.TreinoCorrida;
import com.gabrielodisi.contadorvoltas.repository.TreinoCorridaRepository;
import jakarta.persistence.EntityNotFoundException;
import jakarta.transaction.Transactional;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Optional;

@Service
public class TreinoCorridaService {

    @Autowired
    TreinoCorridaRepository repository;

    public Optional<TreinoCorrida> buscarPorId(Long id) { return repository.findById(id); }

    public TreinoCorrida iniciarTreino(TreinoCorrida treinoCorrida) { return repository.save(treinoCorrida); }

    @Transactional
    public void registrarVolta(Long id, Long tempoVolta){
        Treino treino = repository.findById(id)
                .orElseThrow(() -> new EntityNotFoundException("Treino não encontrado para registrar volta."));

        treino.registrarVolta(tempoVolta);
    }
}
