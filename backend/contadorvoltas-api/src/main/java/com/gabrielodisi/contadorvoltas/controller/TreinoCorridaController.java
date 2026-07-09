package com.gabrielodisi.contadorvoltas.controller;

import com.gabrielodisi.contadorvoltas.model.TreinoCorrida;
import com.gabrielodisi.contadorvoltas.service.TreinoCorridaService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/treinos/corrida")
public class TreinoCorridaController {

    @Autowired
    private TreinoCorridaService service;

    @PostMapping("/iniciar")
    public TreinoCorrida iniciarTreino(@RequestBody TreinoCorrida treinoCorrida) { return service.iniciarTreino(treinoCorrida); }

}
