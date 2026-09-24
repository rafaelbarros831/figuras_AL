#pragma once

#include "Figura.hpp"

// Retangulo com largura e altura independentes.
// Refatoracao do "quad" (figuras_AL-elton_quad): a logica de
// redimensionar e mover, que antes vivia solta em variaveis
// globais e dentro da funcao Geraquad(), agora fica encapsulada
// aqui, seguindo o mesmo padrao das demais Figuras do projeto.
class Retangulo : public Figura
{
public:
    Retangulo(double x, double y, double largura, double altura);

    // Soma deltaLargura/deltaAltura ao tamanho atual e reconstroi
    // os pontos. Use valores negativos para encolher.
    void redimensionar(double deltaLargura, double deltaAltura);

    // Desloca o retangulo em dx/dy e reconstroi os pontos.
    void mover(double dx, double dy);

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
