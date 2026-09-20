
#pragma once

#include <optional>
#include <SFML/Graphics.hpp>
#include "Quadrado.hpp"

class App
{
public:
    App();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void desenharQuadrado();

    sf::RenderWindow window;
    Quadrado quadrado;
};
