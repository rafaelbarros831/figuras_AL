#include "App.hpp"
#include "Transformacao.hpp"

App::App()
    : window(sf::VideoMode({ 600, 400 }), "Transformacao de Figuras")
    , quadrado(200.0, 100.0, 100.0)
{
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
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (event->is<sf::Event::KeyPressed>())
        {
            const auto* tecla =
                event->getIf<sf::Event::KeyPressed>();

            if (tecla->code == sf::Keyboard::Key::Add)
            {
                quadrado.aplicarMatriz(
                    Transformacao::escala(1.1)
                );
            }

            if (tecla->code == sf::Keyboard::Key::Subtract)
            {
                quadrado.aplicarMatriz(
                    Transformacao::escala(0.9)
                );
            }

            if (tecla->code == sf::Keyboard::Key::R)
            {
                quadrado.aplicarMatrizCentrada(
                    Transformacao::reflexaoX()
                );
            }

            if (tecla->code == sf::Keyboard::Key::Left)
            {
                quadrado.aplicarMatrizCentrada(
                    Transformacao::rotacao(-15.0)
                );
            }

            if (tecla->code == sf::Keyboard::Key::Right)
            {
                quadrado.aplicarMatrizCentrada(
                    Transformacao::rotacao(15.0)
                );
            }
        }
    }
}

void App::update()
{
}

void App::render()
{
    window.clear(sf::Color::Blue);

    desenharQuadrado();

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

    forma.setFillColor(sf::Color::Green);

    window.draw(forma);
}