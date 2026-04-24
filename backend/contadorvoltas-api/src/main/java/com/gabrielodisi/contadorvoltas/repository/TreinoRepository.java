package com.gabrielodisi.contadorvoltas.repository;

import com.gabrielodisi.contadorvoltas.model.Treino;
import com.gabrielodisi.contadorvoltas.model.Volta;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.util.List;

public interface TreinoRepository extends JpaRepository<Treino, Long> {

    @Query(value = "SELECT t.* FROM treino t " +
                    "INNER JOIN atleta a ON t.atleta_id = a.id " +
                    "where t.nome like %:nome% AND a.id = :atleta_id", nativeQuery = true)
    List<Treino> buscarTreinosPorNome(@Param("nome") String nome, @Param("atleta_id") long atleta_id);


    @Query(value = "SELECT t.* FROM treino t " +
                    "INNER JOIN atleta a ON t.atleta_id = a.id " +
                    "where t.data_treino like %:data_treino% AND a.id = :atleta_id", nativeQuery = true)
    List<Treino> buscarTreinosPorData(@Param("data_treino") String data_treino, @Param("atleta_id") long atleta_id);


    @Query(value = "SELECT tv.numero_volta, tv.tempo_volta FROM treino_voltas tv " +
                    "INNER JOIN treino t ON (t.id = tv.treino_id) " +
                    "where :id = tv.treino_id", nativeQuery = true)
    List<Volta> listarVoltas(@Param("id") long id);
}
