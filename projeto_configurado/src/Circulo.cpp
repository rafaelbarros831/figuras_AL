#include "Circulo.hpp"

#include <algorithm>

Circulo::Circulo(double centroX, double centroY, double raio)
    : centroX(centroX), centroY(centroY), raio(raio)
{
}

void Circulo::redimensionar(double deltaRaio)
{
    raio += deltaRaio;
}

void Circulo::mover(double dx, double dy)
{
    centroX += dx;
    centroY += dy;
}

void Circulo::resetar(double novoCentroX, double novoCentroY, double novoRaio)
{
    centroX = novoCentroX;
    centroY = novoCentroY;
    raio = novoRaio;
}

void Circulo::limitarA(double largura, double altura)
{
    // std::clamp exige minimo <= maximo; se o circulo nao cabe na
    // area, deixa como esta.
    if (largura >= 2.0 * raio)
        centroX = std::clamp(centroX, raio, largura - raio);

    if (altura >= 2.0 * raio)
        centroY = std::clamp(centroY, raio, altura - raio);
}
