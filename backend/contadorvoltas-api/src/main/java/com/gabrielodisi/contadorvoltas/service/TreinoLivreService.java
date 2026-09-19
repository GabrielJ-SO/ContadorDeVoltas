package com.gabrielodisi.contadorvoltas.service;

import com.gabrielodisi.contadorvoltas.model.treinos.TreinoLivre;
import com.gabrielodisi.contadorvoltas.repository.TreinoLivreRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class TreinoLivreService {

    @Autowired
    private TreinoLivreRepository repository;

    public TreinoLivre iniciarTreino(TreinoLivre treino) { return repository.save(treino); }

}
