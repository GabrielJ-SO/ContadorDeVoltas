package com.gabrielodisi.contadorvoltas.service;

import com.gabrielodisi.contadorvoltas.model.TreinoIntervalado;
import com.gabrielodisi.contadorvoltas.repository.TreinoIntervaladoRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class TreinoIntervaladoService {

    @Autowired
    private TreinoIntervaladoRepository repository;

    public TreinoIntervalado iniciarTreino(TreinoIntervalado treinoIntervalado) { return repository.save(treinoIntervalado); }

}
