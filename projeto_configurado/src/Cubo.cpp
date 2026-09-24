#include "Cubo.hpp"

Cubo::Cubo(double tamanho)
    : tamanhoOriginal(tamanho)
{
    criar(tamanho);
}

void Cubo::criar(double tamanho)
{
    vertices.clear();
    arestas.clear();

    double h = tamanho * 0.5;

    vertices.push_back(Ponto3D(-h, -h, -h));
    vertices.push_back(Ponto3D( h, -h, -h));
    vertices.push_back(Ponto3D( h,  h, -h));
    vertices.push_back(Ponto3D(-h,  h, -h));
    vertices.push_back(Ponto3D(-h, -h,  h));
    vertices.push_back(Ponto3D( h, -h,  h));
    vertices.push_back(Ponto3D( h,  h,  h));
    vertices.push_back(Ponto3D(-h,  h,  h));

    arestas.push_back({0, 1});
    arestas.push_back({1, 2});
    arestas.push_back({2, 3});
    arestas.push_back({3, 0});
    arestas.push_back({4, 5});
    arestas.push_back({5, 6});
    arestas.push_back({6, 7});
    arestas.push_back({7, 4});
    arestas.push_back({0, 4});
    arestas.push_back({1, 5});
    arestas.push_back({2, 6});
    arestas.push_back({3, 7});
}

void Cubo::aplicarMatriz(const Matriz3& matriz)
{
    for (auto& v : vertices)
    {
        v = matriz.aplicar(v);
    }
}

void Cubo::resetar(double tamanho)
{
    tamanhoOriginal = tamanho;
    criar(tamanho);
}

const std::vector<Ponto3D>& Cubo::getVertices() const
{
    return vertices;
}

const std::vector<std::pair<int, int>>& Cubo::getArestas() const
{
    return arestas;
}
