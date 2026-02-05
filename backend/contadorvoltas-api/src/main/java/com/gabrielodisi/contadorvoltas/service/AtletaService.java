package com.gabrielodisi.contadorvoltas.service;

import com.gabrielodisi.contadorvoltas.dto.response.TreinoResponseDTO;
import com.gabrielodisi.contadorvoltas.model.Atleta;
import com.gabrielodisi.contadorvoltas.model.Treino;
import com.gabrielodisi.contadorvoltas.repository.AtletaRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class AtletaService {

    @Autowired
    private AtletaRepository repository;

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

    public List<Treino> listarTreinosDoAtleta(Long id) {
        Optional<Atleta> atleta = repository.findById(id);
        if (atleta.isPresent()) {
            return atleta.get().getTreinos();
        }
        else {
            throw new RuntimeException("Atleta não  encontrado");
        }

    }
}
