package com.gabrielodisi.contadorvoltas.controller;

import com.gabrielodisi.contadorvoltas.model.Volta;
import com.gabrielodisi.contadorvoltas.service.TreinoService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/treinos")
public class TreinoController {

    @Autowired
    private TreinoService service;

    @DeleteMapping("/del/{id}")
    public void deletarTreinoCorrida(@PathVariable Long id) { service.deletar(id); }

    @GetMapping("/buscar/{id}/voltas")
    public List<Volta> buscarVoltas(@PathVariable Long id) { return service.buscarVoltas(id); }
}
