
#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
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

	void initGUI();
    sf::RenderWindow window;
    tgui::Gui gui;

	Quadrado quadrado;

    tgui::Label::Ptr labelMatrizText;
};

