#pragma once

#include "Figura.hpp"

// Representa um retangulo com posicao e dimensoes configuraveis
class Retangulo : public Figura
{
public:
    Retangulo(double x, double y, double largura, double altura);

    // Soma deltaLargura/deltaAltura ao tamanho atual e reconstroi
    // os pontos. Use valores negativos para encolher.
    void redimensionar(double deltaLargura, double deltaAltura);

    // Desloca o retangulo em dx/dy e reconstroi os pontos.
    void mover(double dx, double dy);

    // Redefine posicao e dimensoes originais
    void resetar(double novoX, double novoY, double novaLargura, double novaAltura);

    double getX() const { return x; }
    double getY() const { return y; }
    double getLargura() const { return largura; }
    double getAltura() const { return altura; }

private:
    void atualizarPontos();

    double x;
    double y;
    double largura;
    double altura;
};
