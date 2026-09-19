package com.gabrielodisi.contadorvoltas.controller;

import com.gabrielodisi.contadorvoltas.model.treinos.Treino;
import com.gabrielodisi.contadorvoltas.model.treinos.Volta;
import com.gabrielodisi.contadorvoltas.service.TreinoService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("/treinos")
public class TreinoController {

    @Autowired
    private TreinoService service;

    @DeleteMapping("/del/{id}")
    public void deletar(@PathVariable Long id) { service.deletar(id); }

    @GetMapping("/buscar/{id}/voltas")
    public List<Volta> buscarVoltas(@PathVariable Long id) { return service.buscarVoltas(id); }

    @GetMapping("/buscar/{id}")
    public ResponseEntity<Treino> buscarPorId(@PathVariable Long id) {
        Optional<Treino> treinoCorrida = service.buscarPorId(id);
        return treinoCorrida.map(ResponseEntity::ok)
                .orElseGet(() -> ResponseEntity.notFound().build());
    }

    @PostMapping("/registrar_volta/{id}")
    public ResponseEntity<Void> registrarVolta(@PathVariable Long id, @RequestBody Volta volta) {
        service.registrarVolta(id, (volta.getTempo()));
        return ResponseEntity.ok().build();
    }

    @PostMapping("/concluir/{id}")
    public ResponseEntity<Void> finalizarTreino(@PathVariable Long id) {
        service.finalizarTreino(id);
        return ResponseEntity.ok().build();
    }

    @PostMapping("/iniciar/{id}")
    public ResponseEntity<Void> iniciarTreino(@PathVariable Long id) {
        service.iniciarTreino(id);
        return ResponseEntity.ok().build();
    }

}
