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

protected:
    // Permite que figuras com geometria mutavel (ex.: Retangulo, que
    // muda de tamanho/posicao em tempo real) reconstruam seus pontos.
    void limparPontos();

private:
    Ponto calcularCentro() const;

    std::vector<Ponto> pontos;
};