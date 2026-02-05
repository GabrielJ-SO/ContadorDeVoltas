package com.gabrielodisi.contadorvoltas.dto.response;

import com.gabrielodisi.contadorvoltas.model.Treino;
import com.gabrielodisi.contadorvoltas.model.Volta;

import java.time.LocalDate;
import java.util.List;

public record TreinoResponseDTO (
        Long id,
        String nome,
        LocalDate dataTreino,
        Integer totalVoltas,
        Integer voltasConcluida,
        Long tempo,
        Boolean concluido,
        List<Volta> voltas
    ){

    public TreinoResponseDTO(Treino treino) {
        this(treino.getId(), treino.getNome(), treino.getDataTreino(), treino.getTotalVoltas(),
                treino.getVoltasConcluidas(), treino.getTempo(), treino.isConcluido(), treino.getVoltas());
    }

}
