package com.gabrielodisi.contadorvoltas.repository;

import com.gabrielodisi.contadorvoltas.model.Atleta;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.util.Optional;

public interface AtletaRepository extends JpaRepository<Atleta, Long> {


    @Query(value= "SELECT * FROM atleta" +
                  " WHERE nome LIKE :nome" +
                  " AND senha LIKE :senha", nativeQuery = true)
    Optional<Atleta> buscarIdPorNomeESenha(@Param("nome") String nome, @Param("senha") String senha);


}

