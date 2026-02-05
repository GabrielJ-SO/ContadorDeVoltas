package com.gabrielodisi.contadorvoltas.dto.request;

import jakarta.validation.constraints.NotNull;

public record AtletaRequestDTO(
        @NotNull
        String nome,
        @NotNull
        String sehna) {}


