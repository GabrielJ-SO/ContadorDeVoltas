package com.gabrielodisi.contadorvoltas.controller;

import com.gabrielodisi.contadorvoltas.model.treinos.Tiro;
import com.gabrielodisi.contadorvoltas.model.treinos.TreinoIntervalado;
import com.gabrielodisi.contadorvoltas.service.TreinoIntervaladoService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/treinos/intervalado")
public class TreinoIntervaladoController {

    @Autowired
    private TreinoIntervaladoService service;

    @PostMapping("/iniciar")
    public TreinoIntervalado iniciarTreino(@RequestBody TreinoIntervalado treino) { return service.iniciarTreino(treino); }

    @GetMapping("/tiros/{id}")
    public List<Tiro> listarTiros(@PathVariable Long id){ return service.listarTiros(id); }


}
