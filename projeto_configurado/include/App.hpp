#pragma once

#include <optional>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Quadrado.hpp"
#include "Retangulo.hpp"
#include "Triangulo.hpp"
#include "Cubo.hpp"
#include "Circulo.hpp"
#include "GradeQuadrados.hpp"
#include "Matriz.hpp"
#include "Matriz3.hpp"

// Modo da aplicacao: 2D ou 3D
enum class ModoApp
{
    Modo2D,
    Modo3D
};

// Qual figura esta ativa para receber as transformacoes
enum class TipoFigura
{
    Quadrado,
    Retangulo,
    Triangulo,
    Circulo,
    Grade
};

// Botao visual da interface
struct BotaoUI
{
    std::string id;
    std::string texto;
    sf::FloatRect bounds;
    bool ativo = false;
    bool hover = false;
    sf::Color corNormal = sf::Color(38, 48, 64);
    sf::Color corHover = sf::Color(55, 70, 95);
    sf::Color corAtivo = sf::Color(37, 99, 235);
};

class App
{
public:
    App(int linhasGrade, int colunasGrade);
    void run();

private:
    void processEvents();
    void update();
    void render();

    // Eventos de clique e mouse
    void tratarCliqueMouse(const sf::Vector2i& pos);
    void tratarMovimentoMouse(const sf::Vector2i& pos);
    void tratarSoltarMouse();
    void tratarDigitacaoTexto(char32_t unicode);
    void executarAcaoBotao(const std::string& id);

    // Transformacoes 2D
    void aplicarMatrizManual(double a, double b, double c, double d);
    void aplicarEscala2D(double fator);
    void aplicarRotacao2D(double angulo);
    void aplicarReflexaoX2D();
    void aplicarReflexaoY2D();
    void aplicarReflexaoOrigem2D();
    void transladarFigura2D(double dx, double dy);
    void resetarFigura2D();

    // Transformacoes 3D do Cubo
    void aplicarRotacaoX3D(double angulo);
    void aplicarRotacaoY3D(double angulo);
    void aplicarRotacaoZ3D(double angulo);
    void aplicarEscala3D(double fator);
    void resetar3D();

    // Desenho na tela
    void renderizarPainelUI();
    void renderizarCanvas();
    void desenharFigura(const Figura& figura, const sf::Color& corPreenchimento, const sf::Color& corBorda, float espessuraBorda = 1.5f);
    void desenharQuadrado();
    void desenharRetangulo();
    void desenharTriangulo();
    void desenharCubo();
    void desenharCirculo();
    void desenharGrade();
    void desenharEixosCartesianos();
    void desenharTexto(const std::string& str, float x, float y, unsigned int tam, const sf::Color& cor = sf::Color::White, bool negrito = false);

    sf::Vector2f projetar(const Ponto3D& p) const;
    void inicializarBotoes();

    // Janela SFML e fonte
    sf::RenderWindow window;
    sf::Font fonte;
    bool fonteCarregada;

    ModoApp modoAtual;
    TipoFigura figuraSelecionada;
    std::vector<BotaoUI> botoes;

    // Campos de entrada para digitar a matriz 2x2 diretamente na interface
    int campoMatrizFocado; // 0: a, 1: b, 2: c, 3: d, -1: nenhum
    std::string strMatrizA;
    std::string strMatrizB;
    std::string strMatrizC;
    std::string strMatrizD;

    // Botoes para ligar/desligar cada figura na tela
    bool mostrarQuadrado;
    bool mostrarRetangulo;
    bool mostrarTriangulo;
    bool mostrarCirculo;
    bool mostrarGrade;

    // Matrizes acumuladas em exibicao
    Matriz matrizAcumulada2D;
    Matriz3 matrizAcumulada3D;

    // Objetos das figuras
    Quadrado quadrado;
    Retangulo retangulo;
    Triangulo triangulo;
    Cubo cubo;
    Circulo circulo;
    GradeQuadrados grade;

    // Câmera 3D e giro
    double distanciaCamera;
    bool autoGiro3D;

    // Arrastar com o mouse
    bool arrastandoMouse;
    sf::Vector2i ultimaPosMouse;
};
