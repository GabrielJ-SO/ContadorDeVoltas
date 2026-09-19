package com.gabrielodisi.contadorvoltas.controller;

import com.gabrielodisi.contadorvoltas.model.treinos.TreinoIntervalado;
import com.gabrielodisi.contadorvoltas.service.TreinoIntervaladoService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/treinos/intervalado")
public class TreinoIntervaladoController {

    @Autowired
    private TreinoIntervaladoService service;

    @PostMapping("/iniciar")
    public TreinoIntervalado iniciarTreino(@RequestBody TreinoIntervalado treino) { return service.iniciarTreino(treino); }

}
