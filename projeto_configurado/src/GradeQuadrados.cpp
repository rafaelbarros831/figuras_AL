#include "GradeQuadrados.hpp"

namespace
{
    // Espacamento e tamanho padrao dos quadradinhos
    const double ORIGEM_X = 40.0;
    const double ORIGEM_Y = 10.0;
    const double LADO = 20.0;
    const double ESPACAMENTO = 10.0;
}

GradeQuadrados::GradeQuadrados(int linhas, int colunas)
    : linhas(linhas), colunas(colunas)
{
    criar();
}

void GradeQuadrados::criar()
{
    quadrados.clear();
    quadrados.reserve(static_cast<std::size_t>(linhas) * static_cast<std::size_t>(colunas));

    const double passo = LADO + ESPACAMENTO;

    for (int i = 0; i < linhas; ++i)
    {
        for (int j = 0; j < colunas; ++j)
        {
            quadrados.emplace_back(ORIGEM_X + j * passo, ORIGEM_Y + i * passo, LADO);
        }
    }
}

void GradeQuadrados::aplicarMatriz(const Matriz& matriz)
{
    for (auto& q : quadrados)
    {
        q.aplicarMatrizCentrada(matriz);
    }
}

void GradeQuadrados::transladar(double dx, double dy)
{
    for (auto& q : quadrados)
    {
        q.transladar(dx, dy);
    }
}

void GradeQuadrados::resetar()
{
    criar();
}
