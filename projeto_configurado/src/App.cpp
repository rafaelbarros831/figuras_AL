#include "App.hpp"
#include "Transformacao.hpp"
#include "Transformacao3D.hpp"

App::App()
    : window(sf::VideoMode({ 900, 600 }), "Transformacao de Figuras + Cubo 3D")
    , quadrado(80.0, 80.0, 90.0)
    , retangulo(80.0, 250.0, 110.0, 70.0)
    , cubo(160.0)
    , distanciaCamera(450.0)
{
    window.setFramerateLimit(60);
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
            const auto* tecla = event->getIf<sf::Event::KeyPressed>();

            if (tecla->code == sf::Keyboard::Key::Add || tecla->code == sf::Keyboard::Key::Equal)
            {
                quadrado.aplicarMatrizCentrada(Transformacao::escala(1.1));
                cubo.aplicarMatriz(Transformacao3D::escala(1.1));
            }

            if (tecla->code == sf::Keyboard::Key::Subtract || tecla->code == sf::Keyboard::Key::Hyphen)
            {
                quadrado.aplicarMatrizCentrada(Transformacao::escala(0.9));
                cubo.aplicarMatriz(Transformacao3D::escala(0.9));
            }

            if (tecla->code == sf::Keyboard::Key::R)
            {
                quadrado.aplicarMatrizCentrada(Transformacao::reflexaoX());
            }

            if (tecla->code == sf::Keyboard::Key::T)
            {
                quadrado.aplicarMatrizCentrada(Transformacao::reflexaoY());
            }

            if (tecla->code == sf::Keyboard::Key::Comma)
            {
                quadrado.aplicarMatrizCentrada(Transformacao::rotacao(-15.0));
            }

            if (tecla->code == sf::Keyboard::Key::Period)
            {
                quadrado.aplicarMatrizCentrada(Transformacao::rotacao(15.0));
            }

            if (tecla->code == sf::Keyboard::Key::Q)
            {
                quadrado = Quadrado(80.0, 80.0, 90.0);
                cubo.resetar(160.0);
            }
        }
    }
}

void App::update()
{
    atualizarRetangulo();

    const double angulo = 1.5;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        cubo.aplicarMatriz(Transformacao3D::rotacaoY(-angulo));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        cubo.aplicarMatriz(Transformacao3D::rotacaoY(angulo));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        cubo.aplicarMatriz(Transformacao3D::rotacaoX(-angulo));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        cubo.aplicarMatriz(Transformacao3D::rotacaoX(angulo));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
        cubo.aplicarMatriz(Transformacao3D::rotacaoZ(-angulo));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
        cubo.aplicarMatriz(Transformacao3D::rotacaoZ(angulo));
}

void App::atualizarRetangulo()
{
    const double PASSO_TAMANHO = 0.05;
    const double PASSO_POSICAO = 0.25;

    const double TAMANHO_MINIMO = 10.0;
    const double TAMANHO_MAXIMO = 250.0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)
        && retangulo.getLargura() > TAMANHO_MINIMO
        && retangulo.getAltura() > TAMANHO_MINIMO)
    {
        retangulo.redimensionar(-PASSO_TAMANHO, -PASSO_TAMANHO);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)
        && retangulo.getLargura() < TAMANHO_MAXIMO
        && retangulo.getAltura() < TAMANHO_MAXIMO)
    {
        retangulo.redimensionar(PASSO_TAMANHO, PASSO_TAMANHO);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        retangulo.mover(0.0, -PASSO_POSICAO);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        retangulo.mover(0.0, PASSO_POSICAO);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        retangulo.mover(-PASSO_POSICAO, 0.0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        retangulo.mover(PASSO_POSICAO, 0.0);
    }
}

sf::Vector2f App::projetar(const Ponto3D& p) const
{
    double z = p.getZ() + distanciaCamera;
    if (z < 1.0) z = 1.0;

    double fator = distanciaCamera / z;

    float x = static_cast<float>(p.getX() * fator + 650.0);
    float y = static_cast<float>(-p.getY() * fator + 300.0);

    return sf::Vector2f(x, y);
}

void App::render()
{
    window.clear(sf::Color(25, 25, 40));

    desenharQuadrado();
    desenharRetangulo();
    desenharCubo();

    window.display();
}

void App::desenharQuadrado()
{
    const auto& pontos = quadrado.getPontos();

    sf::ConvexShape forma;
    forma.setPointCount(static_cast<std::size_t>(pontos.size()));

    for (std::size_t i = 0; i < pontos.size(); ++i)
    {
        forma.setPoint(i, sf::Vector2f(
            static_cast<float>(pontos[i].getX()),
            static_cast<float>(pontos[i].getY())
        ));
    }

    forma.setFillColor(sf::Color(50, 200, 80));
    forma.setOutlineColor(sf::Color::White);
    forma.setOutlineThickness(1.5f);
    window.draw(forma);
}

void App::desenharRetangulo()
{
    const auto& pontos = retangulo.getPontos();

    sf::ConvexShape forma;
    forma.setPointCount(static_cast<std::size_t>(pontos.size()));

    for (std::size_t i = 0; i < pontos.size(); ++i)
    {
        forma.setPoint(i, sf::Vector2f(
            static_cast<float>(pontos[i].getX()),
            static_cast<float>(pontos[i].getY())
        ));
    }

    forma.setFillColor(sf::Color(200, 60, 80));
    forma.setOutlineColor(sf::Color::White);
    forma.setOutlineThickness(1.5f);
    window.draw(forma);
}

void App::desenharCubo()
{
    const auto& vertices = cubo.getVertices();
    const auto& arestas = cubo.getArestas();

    for (const auto& aresta : arestas)
    {
        sf::Vector2f p1 = projetar(vertices[aresta.first]);
        sf::Vector2f p2 = projetar(vertices[aresta.second]);

        sf::VertexArray linha(sf::PrimitiveType::Lines, 2);
        linha[0].position = p1;
        linha[0].color = sf::Color(100, 220, 255);
        linha[1].position = p2;
        linha[1].color = sf::Color(100, 220, 255);

        window.draw(linha);
    }

    for (const auto& v : vertices)
    {
        sf::Vector2f pos = projetar(v);
        sf::CircleShape ponto(3.5f);
        ponto.setOrigin({ 3.5f, 3.5f });
        ponto.setPosition(pos);
        ponto.setFillColor(sf::Color(255, 180, 40));
        window.draw(ponto);
    }
}