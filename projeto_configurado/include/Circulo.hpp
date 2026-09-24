#pragma once

// Representa um circulo com centro (x, y) e raio
class Circulo
{
public:
    Circulo(double centroX, double centroY, double raio);

    // Soma deltaRaio ao raio atual. Use valores negativos para encolher.
    void redimensionar(double deltaRaio);

    // Desloca o centro em dx/dy.
    void mover(double dx, double dy);

    // Reseta posicao e raio
    void resetar(double novoCentroX, double novoCentroY, double novoRaio);

    // Mantem o circulo inteiro dentro de uma area (0,0)-(largura,altura).
    void limitarA(double largura, double altura);

    double getCentroX() const { return centroX; }
    double getCentroY() const { return centroY; }
    double getRaio() const { return raio; }

private:
    double centroX;
    double centroY;
    double raio;
};
