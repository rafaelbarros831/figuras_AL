#include "Retangulo.hpp"

Retangulo::Retangulo(double x, double y, double largura, double altura)
    : x(x), y(y), largura(largura), altura(altura)
{
    atualizarPontos();
}

void Retangulo::redimensionar(double deltaLargura, double deltaAltura)
{
    largura += deltaLargura;
    altura += deltaAltura;
    atualizarPontos();
}

void Retangulo::mover(double dx, double dy)
{
    x += dx;
    y += dy;
    atualizarPontos();
}

void Retangulo::atualizarPontos()
{
    // Mesma ideia do Quadrado::Quadrado, so que reaplicada sempre
    // que x, y, largura ou altura mudam (por isso limparPontos()
    // antes de recriar os 4 cantos: TL, TR, BR, BL).
    limparPontos();

    addPonto(Ponto(x, y));
    addPonto(Ponto(x + largura, y));
    addPonto(Ponto(x + largura, y + altura));
    addPonto(Ponto(x, y + altura));
}
