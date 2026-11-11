package com.gabrielodisi.contadorvoltas.repository;

import com.gabrielodisi.contadorvoltas.model.treinos.TreinoCorrida;
import org.springframework.data.jpa.repository.JpaRepository;

public interface TreinoCorridaRepository extends JpaRepository<TreinoCorrida, Long> {

}
