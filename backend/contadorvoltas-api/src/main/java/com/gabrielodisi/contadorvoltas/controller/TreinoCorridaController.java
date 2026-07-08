package com.gabrielodisi.contadorvoltas.controller;

import com.gabrielodisi.contadorvoltas.model.TreinoCorrida;
import com.gabrielodisi.contadorvoltas.model.Volta;
import com.gabrielodisi.contadorvoltas.service.TreinoCorridaService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.Optional;

@RestController
@RequestMapping("/treinos/corrida")
public class TreinoCorridaController {

    @Autowired
    private TreinoCorridaService service;

    @PostMapping("/iniciar")
    public TreinoCorrida iniciarTreino(@RequestBody TreinoCorrida treinoCorrida) { return service.iniciarTreino(treinoCorrida); }

    @PostMapping("/registrar_volta/{id}")
    public ResponseEntity<Void> registrarVolta(@PathVariable Long id, @RequestBody Volta volta) {
        service.registrarVolta(id, (volta.getTempo()) );
        return ResponseEntity.ok().build();
    }

    @GetMapping("/buscar/{id}")
    public ResponseEntity<TreinoCorrida> buscarPorId(@PathVariable Long id) {
        Optional<TreinoCorrida> treinoCorrida = service.buscarPorId(id);
        return treinoCorrida.map(ResponseEntity::ok)
                .orElseGet(() -> ResponseEntity.notFound().build());
    }

}
