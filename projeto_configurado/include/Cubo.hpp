#pragma once

#include <vector>
#include <utility>
#include "Ponto3D.hpp"
#include "Matriz3.hpp"

class Cubo
{
public:
    Cubo(double tamanho);

    void aplicarMatriz(const Matriz3& matriz);
    void resetar(double tamanho);

    const std::vector<Ponto3D>& getVertices() const;
    const std::vector<std::pair<int, int>>& getArestas() const;

private:
    void criar(double tamanho);

    std::vector<Ponto3D> vertices;
    std::vector<std::pair<int, int>> arestas;
    double tamanhoOriginal;
};
