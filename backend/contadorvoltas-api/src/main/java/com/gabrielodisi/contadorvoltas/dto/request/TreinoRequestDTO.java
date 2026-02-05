package com.gabrielodisi.contadorvoltas.dto.request;

import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Positive;

public record TreinoRequestDTO(
        @NotNull
        @Positive
        Integer totalVoltas,
        @NotNull
        String nome) {}



