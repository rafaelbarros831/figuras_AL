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
    void aplicarMatrizCentrada(const Matriz& matriz);
    void transladar(double dx, double dy);

    const std::vector<Ponto>& getPontos() const
    {
        return pontos;
    }

private:
    Ponto calcularCentro() const;

    std::vector<Ponto> pontos;
};