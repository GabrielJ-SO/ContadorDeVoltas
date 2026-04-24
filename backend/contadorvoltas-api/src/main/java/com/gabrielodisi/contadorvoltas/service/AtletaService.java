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

    public List<Atleta> listar() { return repository.findAll(); }

    public Optional<Atleta> buscarPorId(Long id) { return repository.findById(id); }

    public Atleta salvar(Atleta atleta) { return repository.save(atleta); }

    public Atleta atualizar(Long id, Atleta atletaAtualizado) {
        if (!repository.existsById(id)) {
            return null;
        }
        atletaAtualizado.setId(id);
        return salvar(atletaAtualizado);
    }

    public void deletar(Long id) {
        if (repository.existsById(id)) {
            repository.deleteById(id);
        }
        else {
            throw new RuntimeException("Atleta não encontrado");
        }
    }

    public Optional<Atleta> fazerLogin(String nome, String senha) {
        Optional<Atleta> atleta = repository.buscarIdPorNomeESenha(nome, senha);

        if (atleta.isPresent()) {
            return atleta;
        }
        else {
            throw new RuntimeException("Atleta não encontrado.");
        }
    }

    public List<Treino> listarTreinosDoAtleta(Long id) {
        Optional<Atleta> atleta = repository.findById(id);
        if (atleta.isPresent()) {
            return atleta.get().getTreinos();
        } else {
            throw new RuntimeException("Atleta não encontrado.");
        }

    }

    public List<Treino> buscarTreinosPorNome(Long atleta_id, String nome) {
        Optional<Atleta> atleta = repository.findById(atleta_id);
        if (atleta.isPresent()) {
            return treinoRepository.buscarTreinosPorNome(nome, atleta_id);
        }
        else {
            throw new RuntimeException("Atleta não encontrado.");
        }
    }

    public  List<Treino> buscarTreinosPorData(Long atleta_id, String data) {
        Optional<Atleta> atleta = repository.findById(atleta_id);
        if (atleta.isPresent()) {
            return treinoRepository.buscarTreinosPorData(data, atleta_id);
        }
        else {
            throw new RuntimeException("Atleta não encontrado.");
        }
    }
}
