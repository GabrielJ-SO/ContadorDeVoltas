package com.gabrielodisi.contadorvoltas.service;

import com.gabrielodisi.contadorvoltas.model.treinos.Treino;
import com.gabrielodisi.contadorvoltas.model.treinos.Volta;
import com.gabrielodisi.contadorvoltas.repository.TreinoRepository;
import jakarta.persistence.EntityNotFoundException;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.transaction.Transactional;
import jakarta.validation.constraints.Null;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class TreinoService {

    @Autowired
    private TreinoRepository repository;
    @Autowired
    private HttpServletResponse httpServletResponse;

    public List<Treino> listar() { return repository.findAll(); }

    public Optional<Treino> buscarPorId(Long id) { return repository.findById(id); }

    @Transactional
    public void iniciarTreino(long id, long atleta_id) {
        Treino treino = repository.findById(id)
                .orElseThrow(() -> new EntityNotFoundException("Treino não encontrado."));

        if (verificarTreinoEmAndamento(atleta_id) != null)
            throw new RuntimeException("Já possui um treino em andamento.");

        if (!treino.iniciarTreino())
            throw new RuntimeException("Não foi possível iniciar o Treino.");

    }

    @Transactional
    public void finalizarTreino(long id) {
        Treino treino = repository.findById(id)
                .orElseThrow(() -> new EntityNotFoundException("Treino não encontrado."));

        treino.finalizarTreino();
    }

    public void deletar(Long id) {
        if (repository.existsById(id)) {
            repository.deleteById(id);
        }
        else {
            throw new RuntimeException("Treino não encontrado");
        }
    }

    public List<Volta> buscarVoltas(Long id){
        Treino treino = repository.findById(id)
                .orElseThrow(() -> new EntityNotFoundException("Treino não encontrado."));

        return treino.getVoltas();
    }

    @Transactional
    public void registrarVolta(Long id, Long tempoVolta) {
        Treino treino = repository.findById(id)
                .orElseThrow(() -> new EntityNotFoundException("Treino não encontrado para registrar volta."));

        if (!treino.registrarVolta(tempoVolta)) {
            throw new RuntimeException("Erro ao registrar volta.");
        }
    }

    public Treino verificarTreinoEmAndamento(Long atleta_id) { return repository.verificarTreinoEmAndamento(atleta_id); }



}
