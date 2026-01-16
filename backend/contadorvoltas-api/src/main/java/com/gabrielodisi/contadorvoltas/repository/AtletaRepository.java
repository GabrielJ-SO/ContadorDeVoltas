package com.gabrielodisi.contadorvoltas.repository;

import com.gabrielodisi.contadorvoltas.model.Atleta;
import org.springframework.data.jpa.repository.JpaRepository;

public interface AtletaRepository extends JpaRepository<Atleta, Long> {}
