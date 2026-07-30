package com.gabrielodisi.contadorvoltas.service;

import com.gabrielodisi.contadorvoltas.model.Atleta;
import com.gabrielodisi.contadorvoltas.model.Treino;
import com.gabrielodisi.contadorvoltas.repository.AtletaRepository;
import com.gabrielodisi.contadorvoltas.repository.TreinoRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class AtletaService {

    @Autowired
    private AtletaRepository repository;
    @Autowired
    private TreinoRepository treinoRepository;

    public Optional<Atleta> buscarPorId(Long id) { return repository.findById(id); }

    public Atleta salvar(Atleta atleta) { return repository.save(atleta); }

    public void deletar(Long id) {
        if (repository.existsById(id)) {
            repository.deleteById(id);
        }
        else {
            throw new RuntimeException("Atleta não encontrado");
        }
    }

    public Optional<Atleta> login(String nome, String senha) {
        Optional<Atleta> atleta = repository.buscarPorNomeESenha(nome, senha);

        if (atleta.isPresent()) {
            return atleta;
        }
        else {
            throw new RuntimeException("Atleta não encontrado.");
        }
    }

    public List<Treino> listarTreinos(Long id) {
        Optional<Atleta> atleta = repository.findById(id);
        if (atleta.isPresent()) {
            return atleta.get().getTreinos();
        }
        else {
            throw new RuntimeException("Atleta não encontrado.");
        }
    }

}
