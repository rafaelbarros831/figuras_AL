#pragma once

#include <vector>
#include "Quadrado.hpp"

// Grade formada por uma matriz de quadrados (linhas x colunas)
class GradeQuadrados
{
public:
    static constexpr int DIMENSAO_MAXIMA = 20;

    GradeQuadrados(int linhas, int colunas);

    void aplicarMatriz(const Matriz& matriz);
    void transladar(double dx, double dy);
    void resetar();

    const std::vector<Quadrado>& getQuadrados() const { return quadrados; }
    int getLinhas() const { return linhas; }
    int getColunas() const { return colunas; }

private:
    void criar();

    int linhas;
    int colunas;
    std::vector<Quadrado> quadrados;
};
