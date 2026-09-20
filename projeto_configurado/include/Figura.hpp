#pragma once

#include <vector>
#include "Ponto.hpp"
#include "Matriz.hpp"

class Figura
{
public:
    Figura();

    void addPonto(const Ponto& ponto);
    void aplicarMatriz(const Matriz& matriz);

    const std::vector<Ponto>& getPontos() const
    {
        return pontos;
    }

private:
    std::vector<Ponto> pontos;
};