package com.gabrielodisi.contadorvoltas.controller;

import com.gabrielodisi.contadorvoltas.model.Atleta;
import com.gabrielodisi.contadorvoltas.model.Treino;
import com.gabrielodisi.contadorvoltas.service.AtletaService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("/atleta")
public class AtletaController {

    @Autowired
    private AtletaService service;

    @PostMapping
    public Atleta salvar(@RequestBody Atleta atleta){ return service.salvar(atleta); }

    @DeleteMapping("/{id}")
    public void deletarAtleta(@PathVariable Long id){ service.deletar(id); }

    @GetMapping("/{id}")
    public ResponseEntity<Atleta> buscarPorId(@PathVariable Long id){
        Optional<Atleta> atleta = service.buscarPorId(id);
        return atleta.map(ResponseEntity::ok)
                .orElseGet(() -> ResponseEntity.notFound().build());
    }

    @GetMapping("/login/{nome}/{senha}")
    public ResponseEntity<Atleta> login(@PathVariable String nome, @PathVariable String senha) {
        Optional<Atleta> atleta = service.login(nome, senha);
        return atleta.map(ResponseEntity::ok)
                .orElseGet(() -> ResponseEntity.notFound().build());
    }

    @GetMapping("/{id}/treinos")
    public ResponseEntity<List<Treino>> listarTreinos(@PathVariable Long id){
        Optional<List<Treino>> treinos = Optional.ofNullable(service.listarTreinos(id));
        return treinos.map(ResponseEntity::ok)
                .orElseGet(() -> ResponseEntity.notFound().build());
    }

}
