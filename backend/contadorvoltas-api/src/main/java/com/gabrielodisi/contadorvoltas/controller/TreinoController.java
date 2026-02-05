package com.gabrielodisi.contadorvoltas.controller;

import com.gabrielodisi.contadorvoltas.dto.request.RegistrarVoltaRequestDTO;
import com.gabrielodisi.contadorvoltas.model.Treino;
import com.gabrielodisi.contadorvoltas.service.TreinoService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;


import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("/treinos")
public class TreinoController {

    @Autowired
    private TreinoService service;

    @GetMapping
    public List<Treino> listar(){ return service.listar(); }

    @GetMapping("/{id}")
    public ResponseEntity<Treino> buscarPorId(@PathVariable Long id){
        Optional<Treino> treino = service.buscarPorId(id);

        return treino.map(ResponseEntity::ok)
                .orElseGet(() -> ResponseEntity.notFound().build());
    }

    @PostMapping
    public ResponseEntity<Treino> salvar(@RequestBody Treino treino) {
        Treino salvo = service.salvar(treino);
        return ResponseEntity
                .status(HttpStatus.CREATED)
                .body(salvo);
    }

    @PostMapping("/{id}/voltas")
    public ResponseEntity<Void> registrarVolta(
            @PathVariable Long id,
            @RequestBody RegistrarVoltaRequestDTO request) {

        service.registrarVolta(id, (request.tempoVolta()) );

        return ResponseEntity.ok().build();
    }

}
