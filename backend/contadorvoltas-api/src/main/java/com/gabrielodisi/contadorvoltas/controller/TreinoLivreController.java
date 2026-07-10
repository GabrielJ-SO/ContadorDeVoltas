package com.gabrielodisi.contadorvoltas.controller;

import com.gabrielodisi.contadorvoltas.model.TreinoLivre;
import com.gabrielodisi.contadorvoltas.service.TreinoLivreService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/treinos/livre")
public class TreinoLivreController {

    @Autowired
    TreinoLivreService service;

    @PostMapping("/iniciar")
    public TreinoLivre iniciarTreino(@RequestBody TreinoLivre treino) { return service.iniciarTreino(treino); }

}
