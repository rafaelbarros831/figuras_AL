#include "App.hpp"
#include "Transformacao.hpp"
#include <iostream>

App::App()

    : window(sf::VideoMode({ 1000, 600 }), "Transformacao de Figuras - CG")
    , gui(window)
    , quadrado(200.0, 150.0, 100.0)
{
    initGUI();
}

void App::initGUI()
{
    
    auto painelLateral = tgui::Panel::create();
    painelLateral->setPosition("60%", "0%");
    painelLateral->setSize("40%", "100%");
    painelLateral->getRenderer()->setBackgroundColor(sf::Color(60, 60, 60));
    gui.add(painelLateral);

  
    auto labelTitulo = tgui::Label::create("Ambiente lateral com botões");
    labelTitulo->setPosition("10%", "3%");
    labelTitulo->getRenderer()->setTextColor(sf::Color::White);
    painelLateral->add(labelTitulo);

   
    auto btnQuadrado = tgui::Button::create("Quadrado");
    btnQuadrado->setPosition("10%", "8%");
    btnQuadrado->setSize("35%", "40");
    painelLateral->add(btnQuadrado);

    auto btnTriangulo = tgui::Button::create("Triângulo");
    btnTriangulo->setPosition("55%", "8%");
    btnTriangulo->setSize("35%", "40");
    painelLateral->add(btnTriangulo);

   
    auto labelTransf = tgui::Label::create("Transformações Dinâmicas");
    labelTransf->setPosition("10%", "20%");
    labelTransf->getRenderer()->setTextColor(sf::Color::White);
    painelLateral->add(labelTransf);

    
    auto labelEscalaX = tgui::Label::create("Escala X:");
    labelEscalaX->setPosition("10%", "26%");
    painelLateral->add(labelEscalaX);

    auto sliderEscalaX = tgui::Slider::create(0.1f, 3.0f);
    sliderEscalaX->setPosition("35%", "26%");
    sliderEscalaX->setSize("55%", "18");
    sliderEscalaX->setValue(1.0f);
    painelLateral->add(sliderEscalaX);

   
    auto labelRotacao = tgui::Label::create("Rotação (°):");
    labelRotacao->setPosition("10%", "34%");
    painelLateral->add(labelRotacao);

    auto sliderRotacao = tgui::Slider::create(0.0f, 360.0f);
    sliderRotacao->setPosition("35%", "34%");
    sliderRotacao->setSize("55%", "18");
    painelLateral->add(sliderRotacao);

  
    auto labelMatrizTitulo = tgui::Label::create("Visualização Matricial Composite T");
    labelMatrizTitulo->setPosition("10%", "45%");
    painelLateral->add(labelMatrizTitulo);

    auto painelVerde = tgui::Panel::create();
    painelVerde->setPosition("10%", "50%");
    painelVerde->setSize("80%", "100");
    painelVerde->getRenderer()->setBackgroundColor(sf::Color(46, 139, 87)); 
    painelLateral->add(painelVerde);

    labelMatrizText = tgui::Label::create("[ 1.0  0.0 ]\n[ 0.0  1.0 ]");
    labelMatrizText->setPosition("20%", "25%");
    labelMatrizText->setTextSize(18);
    labelMatrizText->getRenderer()->setTextColor(sf::Color::White);
    painelVerde->add(labelMatrizText);

    
    auto labelInput = tgui::Label::create("Digitar valor da matriz:");
    labelInput->setPosition("10%", "72%");
    painelLateral->add(labelInput);

    auto campoTexto = tgui::EditBox::create();
    campoTexto->setPosition("10%", "78%");
    campoTexto->setSize("80%", "30");
    campoTexto->setDefaultText("Ex: 1.5");
    painelLateral->add(campoTexto);

    
    sliderEscalaX->onValueChange([this](float valor) {
        quadrado.aplicarMatriz(Transformacao::escala(valor));
        labelMatrizText->setText("[ " + std::to_string(valor).substr(0, 3) + "  0.0 ]\n[ 0.0  " + std::to_string(valor).substr(0, 3) + " ]");
        });
}

void App::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void App::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        
        gui.handleEvent(*event);

        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}

void App::update()
{
}

void App::render()
{
    window.clear(sf::Color(30, 30, 30));

    desenharQuadrado();

   
    gui.draw();

    window.display();
}

void App::desenharQuadrado()
{
    const auto& pontos = quadrado.getPontos();

    sf::ConvexShape forma;
    forma.setPointCount(4);

    for (std::size_t i = 0; i < pontos.size(); ++i)
    {
        forma.setPoint(
            i,
            sf::Vector2f(
                static_cast<float>(pontos[i].getX()),
                static_cast<float>(pontos[i].getY())
            )
        );
    }

    forma.setFillColor(sf::Color::Red);
    window.draw(forma);
}