package com.gabrielodisi.contadorvoltas.repository;

import com.gabrielodisi.contadorvoltas.model.treinos.Tiro;
import com.gabrielodisi.contadorvoltas.model.treinos.TreinoIntervalado;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.util.List;

public interface TreinoIntervaladoRepository extends JpaRepository<TreinoIntervalado, Long> {

    @Query(value = "SELECT t.*" +
                   " FROM tiro t" +
                    " WHERE t.treino_id = :id;", nativeQuery = true)
    List<Tiro> listarTiros(@Param("id") long id);
}
