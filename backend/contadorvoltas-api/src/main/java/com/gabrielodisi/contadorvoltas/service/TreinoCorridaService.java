package com.gabrielodisi.contadorvoltas.service;

import com.gabrielodisi.contadorvoltas.model.TreinoCorrida;
import com.gabrielodisi.contadorvoltas.repository.TreinoCorridaRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class TreinoCorridaService {

    @Autowired
    TreinoCorridaRepository repository;

    public TreinoCorrida iniciarTreino(TreinoCorrida treinoCorrida) { return repository.save(treinoCorrida); }

}
