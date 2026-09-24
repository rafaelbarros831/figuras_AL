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

void Retangulo::resetar(double novoX, double novoY, double novaLargura, double novaAltura)
{
    x = novoX;
    y = novoY;
    largura = novaLargura;
    altura = novaAltura;
    atualizarPontos();
}

void Retangulo::atualizarPontos()
{
    // Limpa e remonta os 4 vertices com as dimensoes atuais
    limparPontos();

    addPonto(Ponto(x, y));
    addPonto(Ponto(x + largura, y));
    addPonto(Ponto(x + largura, y + altura));
    addPonto(Ponto(x, y + altura));
}
