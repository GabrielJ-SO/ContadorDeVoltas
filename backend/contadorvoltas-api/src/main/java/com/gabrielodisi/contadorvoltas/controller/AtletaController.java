package com.gabrielodisi.contadorvoltas.controller;

import com.gabrielodisi.contadorvoltas.model.Atleta;
import com.gabrielodisi.contadorvoltas.model.Treino;
import com.gabrielodisi.contadorvoltas.service.AtletaService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDate;
import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("/atletas")
public class AtletaController {

    @Autowired
    private AtletaService service;


    @GetMapping
    public List<Atleta> listar() { return service.listar(); }


    @GetMapping("/{id}")
    public ResponseEntity<Atleta> buscarPorId(@PathVariable Long id) {
        Optional<Atleta> atleta = service.buscarPorId(id);
        return atleta.map(ResponseEntity::ok)
                .orElseGet(() -> ResponseEntity.notFound().build());
    }


    @PostMapping
    public Atleta salvar(@RequestBody Atleta atleta) { return service.salvar(atleta); }


    @PutMapping("/{id}")
    public ResponseEntity<Atleta> atualizar(@PathVariable Long id, @RequestBody Atleta atleta) {
        Atleta atletaSalvo = service.atualizar(id, atleta);

        if (atletaSalvo != null) {
            return ResponseEntity.ok(atletaSalvo);
        }
        return ResponseEntity.notFound().build();
    }


    @GetMapping("/{id}/treinos")
    public ResponseEntity<List<Treino>> listarTreinos(@PathVariable Long id) {
        Optional<List<Treino>> treinos = Optional.ofNullable(service.listarTreinosDoAtleta(id));
        return  treinos.map(ResponseEntity::ok)
                .orElseGet(() -> ResponseEntity.notFound().build());
    }


    @GetMapping("/{id}/treinos/nome/{nome}")
    public ResponseEntity<List<Treino>> listarTreinosPorNome(@PathVariable Long id, @PathVariable String nome) {
        Optional<List<Treino>> treinos = Optional.ofNullable((service.buscarTreinosPorNome(id, nome)));
        return treinos.map(ResponseEntity::ok)
                .orElseGet(() -> ResponseEntity.notFound().build());
    }


    @GetMapping("/{id}/treinos/data/{data}")
    public ResponseEntity<List<Treino>> listarTreinosPorData(@PathVariable Long id, @PathVariable String data) {
        Optional<List<Treino>> treinos = Optional.ofNullable((service.buscarTreinosPorData(id, data)));
        return treinos.map(ResponseEntity::ok)
                .orElseGet(() -> ResponseEntity.notFound().build());
    }


    @DeleteMapping("/{id}")
    public void deletarAtleta(@PathVariable Long id){ service.deletar(id); }

}
