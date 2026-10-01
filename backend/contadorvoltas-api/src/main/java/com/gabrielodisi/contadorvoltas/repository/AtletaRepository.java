package com.gabrielodisi.contadorvoltas.repository;

import com.gabrielodisi.contadorvoltas.model.Atleta;
import com.gabrielodisi.contadorvoltas.model.treinos.Treino;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.util.List;
import java.util.Optional;

public interface AtletaRepository extends JpaRepository<Atleta, Long> {


    @Query(value= "SELECT * FROM atleta" +
                  " WHERE nome LIKE :nome" +
                  " AND senha LIKE :senha", nativeQuery = true)
    Optional<Atleta> buscarPorNomeESenha(@Param("nome") String nome, @Param("senha") String senha);

    @Query("SELECT t FROM Treino t WHERE t.atleta.id = :id")
    List<Treino> listarTreinosComLimite(@Param("id") long id, Pageable pageable);

}

