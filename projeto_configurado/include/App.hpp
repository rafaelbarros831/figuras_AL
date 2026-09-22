#pragma once

#include <optional>
#include <SFML/Graphics.hpp>
#include "Quadrado.hpp"
#include "Retangulo.hpp"
#include "Cubo.hpp"

class App
{
public:
    App();
    void run();

private:
    void processEvents();
    void update();
    void atualizarRetangulo();
    void render();
    void desenharQuadrado();
    void desenharRetangulo();
    void desenharCubo();
    sf::Vector2f projetar(const Ponto3D& p) const;

    sf::RenderWindow window;
    Quadrado quadrado;
    Retangulo retangulo;
    Cubo cubo;
    double distanciaCamera;
};
