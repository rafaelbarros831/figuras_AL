#include "App.hpp"
#include "Transformacao.hpp"
#include "Transformacao3D.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

namespace
{
    const float LARGURA_PAINEL = 320.0f;
    const float LARGURA_JANELA = 1180.0f;
    const float ALTURA_JANELA = 700.0f;

    std::string formatarNumero(double valor)
    {
        if (std::abs(valor) < 0.005) valor = 0.0;
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(2);
        if (valor >= 0.0) ss << "+";
        ss << valor;
        return ss.str();
    }
}

App::App(int linhasGrade, int colunasGrade)
    : window(sf::VideoMode({ static_cast<unsigned int>(LARGURA_JANELA), static_cast<unsigned int>(ALTURA_JANELA) }),
             "Trabalho de Algebra Linear - Transformacoes e Figuras (Gabriel)",
             sf::Style::Titlebar | sf::Style::Close)
    , fonteCarregada(false)
    , modoAtual(ModoApp::Modo2D)
    , figuraSelecionada(TipoFigura::Quadrado)
    , campoMatrizFocado(-1)
    , strMatrizA("1.0")
    , strMatrizB("0.0")
    , strMatrizC("0.0")
    , strMatrizD("1.0")
    , mostrarQuadrado(true)
    , mostrarRetangulo(true)
    , mostrarTriangulo(true)
    , mostrarCirculo(true)
    , mostrarGrade(true)
    , matrizAcumulada2D(Matriz::identidade())
    , matrizAcumulada3D(Matriz3::identidade())
    , quadrado(580.0, 200.0, 90.0)
    , retangulo(520.0, 360.0, 130.0, 75.0)
    , triangulo(750.0, 140.0, 690.0, 240.0, 810.0, 240.0)
    , cubo(160.0)
    , circulo(750.0, 480.0, 65.0)
    , grade(linhasGrade, colunasGrade)
    , distanciaCamera(450.0)
    , autoGiro3D(false)
    , arrastandoMouse(false)
    , ultimaPosMouse(0, 0)
{
    window.setFramerateLimit(60);

    // Carrega a fonte do Windows para os textos dos botoes
    fonteCarregada = fonte.openFromFile("C:\\Windows\\Fonts\\segoeui.ttf")
                  || fonte.openFromFile("C:\\Windows\\Fonts\\arial.ttf")
                  || fonte.openFromFile("C:\\Windows\\Fonts\\tahoma.ttf");

    inicializarBotoes();
}

void App::inicializarBotoes()
{
    botoes.clear();

    // Abas de navegacao
    botoes.push_back({ "tab_2d", "2D Planas", sf::FloatRect({ 15.f, 48.f }, { 140.f, 28.f }), true, false, sf::Color(38, 48, 64), sf::Color(55, 70, 95), sf::Color(37, 99, 235) });
    botoes.push_back({ "tab_3d", "3D Cubo",   sf::FloatRect({ 165.f, 48.f }, { 140.f, 28.f }), false, false, sf::Color(38, 48, 64), sf::Color(55, 70, 95), sf::Color(37, 99, 235) });

    // Botoes para ligar/desligar cada figura e selecionar a ativa
    botoes.push_back({ "fig_quad",  "[X] Quadrado",  sf::FloatRect({ 15.f, 104.f }, { 90.f, 26.f }), true, false, sf::Color(30, 40, 50), sf::Color(45, 60, 80), sf::Color(16, 185, 129) });
    botoes.push_back({ "fig_ret",   "[X] Retangulo", sf::FloatRect({ 115.f, 104.f }, { 90.f, 26.f }), true, false, sf::Color(30, 40, 50), sf::Color(45, 60, 80), sf::Color(239, 68, 68) });
    botoes.push_back({ "fig_tri",   "[X] Triangulo", sf::FloatRect({ 215.f, 104.f }, { 90.f, 26.f }), true, false, sf::Color(30, 40, 50), sf::Color(45, 60, 80), sf::Color(245, 158, 11) });
    botoes.push_back({ "fig_circ",  "[X] Circulo",   sf::FloatRect({ 15.f, 134.f }, { 140.f, 26.f }), true, false, sf::Color(30, 40, 50), sf::Color(45, 60, 80), sf::Color(14, 165, 233) });
    botoes.push_back({ "fig_grade", "[X] Grade",     sf::FloatRect({ 165.f, 134.f }, { 140.f, 26.f }), true, false, sf::Color(30, 40, 50), sf::Color(45, 60, 80), sf::Color(168, 85, 247) });

    // Campos de entrada para digitar os valores da matriz (a, b, c, d)
    botoes.push_back({ "cell_a", "a: 1.0", sf::FloatRect({ 20.f, 188.f }, { 65.f, 28.f }), false, false, sf::Color(25, 33, 46), sf::Color(40, 52, 70), sf::Color(37, 99, 235) });
    botoes.push_back({ "cell_b", "b: 0.0", sf::FloatRect({ 90.f, 188.f }, { 65.f, 28.f }), false, false, sf::Color(25, 33, 46), sf::Color(40, 52, 70), sf::Color(37, 99, 235) });
    botoes.push_back({ "cell_c", "c: 0.0", sf::FloatRect({ 165.f, 188.f }, { 65.f, 28.f }), false, false, sf::Color(25, 33, 46), sf::Color(40, 52, 70), sf::Color(37, 99, 235) });
    botoes.push_back({ "cell_d", "d: 1.0", sf::FloatRect({ 235.f, 188.f }, { 65.f, 28.f }), false, false, sf::Color(25, 33, 46), sf::Color(40, 52, 70), sf::Color(37, 99, 235) });

    botoes.push_back({ "btn_aplicar_matriz", "✔ Aplicar Matriz",     sf::FloatRect({ 15.f, 222.f }, { 140.f, 28.f }), false, false, sf::Color(22, 101, 52), sf::Color(34, 150, 75), sf::Color(22, 163, 74) });
    botoes.push_back({ "btn_console_matriz", "Digitar no Console",  sf::FloatRect({ 165.f, 222.f }, { 140.f, 28.f }), false, false, sf::Color(38, 48, 64), sf::Color(55, 70, 95) });

    // Presets rápidos
    botoes.push_back({ "pre_id",    "Identidade",  sf::FloatRect({ 15.f, 255.f }, { 68.f, 22.f }), false, false });
    botoes.push_back({ "pre_reflx", "Refl X",      sf::FloatRect({ 88.f, 255.f }, { 68.f, 22.f }), false, false });
    botoes.push_back({ "pre_refly", "Refl Y",      sf::FloatRect({ 161.f, 255.f }, { 68.f, 22.f }), false, false });
    botoes.push_back({ "pre_shear", "Cisalhar",    sf::FloatRect({ 234.f, 255.f }, { 71.f, 22.f }), false, false });

    // Transformacoes rapidas por botoes
    botoes.push_back({ "scale_down", "Escala -10%", sf::FloatRect({ 15.f, 305.f }, { 140.f, 26.f }), false, false });
    botoes.push_back({ "scale_up",   "Escala +10%", sf::FloatRect({ 165.f, 305.f }, { 140.f, 26.f }), false, false });

    botoes.push_back({ "rot_neg", "Rot -15°", sf::FloatRect({ 15.f, 336.f }, { 140.f, 26.f }), false, false });
    botoes.push_back({ "rot_pos", "Rot +15°", sf::FloatRect({ 165.f, 336.f }, { 140.f, 26.f }), false, false });

    // D-Pad de movimento
    botoes.push_back({ "move_up",     "^ Cima",   sf::FloatRect({ 125.f, 390.f }, { 70.f, 24.f }), false, false });
    botoes.push_back({ "move_left",   "< Esq",    sf::FloatRect({ 45.f, 418.f }, { 70.f, 24.f }), false, false });
    botoes.push_back({ "move_center", "Centro",   sf::FloatRect({ 125.f, 418.f }, { 70.f, 24.f }), false, false });
    botoes.push_back({ "move_right",  "Dir >",    sf::FloatRect({ 205.f, 418.f }, { 70.f, 24.f }), false, false });
    botoes.push_back({ "move_down",   "v Baixo",  sf::FloatRect({ 125.f, 446.f }, { 70.f, 24.f }), false, false });

    botoes.push_back({ "reset_2d", "↺ Resetar Figura Ativa", sf::FloatRect({ 15.f, 480.f }, { 290.f, 28.f }), false, false, sf::Color(65, 25, 30), sf::Color(95, 35, 45), sf::Color(220, 38, 38) });

    // Botoes do Modo 3D
    botoes.push_back({ "rot3_xm", "Rot X -15°", sf::FloatRect({ 15.f, 115.f }, { 140.f, 28.f }), false, false });
    botoes.push_back({ "rot3_xp", "Rot X +15°", sf::FloatRect({ 165.f, 115.f }, { 140.f, 28.f }), false, false });
    botoes.push_back({ "rot3_ym", "Rot Y -15°", sf::FloatRect({ 15.f, 150.f }, { 140.f, 28.f }), false, false });
    botoes.push_back({ "rot3_yp", "Rot Y +15°", sf::FloatRect({ 165.f, 150.f }, { 140.f, 28.f }), false, false });
    botoes.push_back({ "rot3_zm", "Rot Z -15°", sf::FloatRect({ 15.f, 185.f }, { 140.f, 28.f }), false, false });
    botoes.push_back({ "rot3_zp", "Rot Z +15°", sf::FloatRect({ 165.f, 185.f }, { 140.f, 28.f }), false, false });

    botoes.push_back({ "scale3_down", "Escala 3D (-)", sf::FloatRect({ 15.f, 235.f }, { 140.f, 28.f }), false, false });
    botoes.push_back({ "scale3_up",   "Escala 3D (+)", sf::FloatRect({ 165.f, 235.f }, { 140.f, 28.f }), false, false });

    botoes.push_back({ "auto_spin", "▶ Auto-Giro: OFF", sf::FloatRect({ 15.f, 285.f }, { 290.f, 32.f }), false, false, sf::Color(25, 55, 40), sf::Color(40, 80, 60), sf::Color(16, 185, 129) });
    botoes.push_back({ "reset_3d",  "↺ Resetar Cubo 3D", sf::FloatRect({ 15.f, 330.f }, { 290.f, 30.f }), false, false, sf::Color(65, 25, 30), sf::Color(95, 35, 45), sf::Color(220, 38, 38) });
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
        else if (event->is<sf::Event::MouseButtonPressed>())
        {
            const auto* mb = event->getIf<sf::Event::MouseButtonPressed>();
            if (mb->button == sf::Mouse::Button::Left)
            {
                tratarCliqueMouse(mb->position);
            }
        }
        else if (event->is<sf::Event::MouseMoved>())
        {
            const auto* mm = event->getIf<sf::Event::MouseMoved>();
            tratarMovimentoMouse(mm->position);
        }
        else if (event->is<sf::Event::MouseButtonReleased>())
        {
            const auto* mr = event->getIf<sf::Event::MouseButtonReleased>();
            if (mr->button == sf::Mouse::Button::Left)
            {
                tratarSoltarMouse();
            }
        }
        else if (event->is<sf::Event::TextEntered>())
        {
            const auto* te = event->getIf<sf::Event::TextEntered>();
            tratarDigitacaoTexto(te->unicode);
        }
        else if (event->is<sf::Event::KeyPressed>())
        {
            const auto* tecla = event->getIf<sf::Event::KeyPressed>();

            // Se nao esta digitando em nenhum campo de texto
            if (campoMatrizFocado < 0)
            {
                // Tab alterna modo 2D / 3D
                if (tecla->code == sf::Keyboard::Key::Tab)
                {
                    if (modoAtual == ModoApp::Modo2D) executarAcaoBotao("tab_3d");
                    else executarAcaoBotao("tab_2d");
                }

                // Escala (+ e -)
                if (tecla->code == sf::Keyboard::Key::Add || tecla->code == sf::Keyboard::Key::Equal)
                {
                    if (modoAtual == ModoApp::Modo2D) aplicarEscala2D(1.1);
                    else aplicarEscala3D(1.1);
                }
                if (tecla->code == sf::Keyboard::Key::Subtract || tecla->code == sf::Keyboard::Key::Hyphen)
                {
                    if (modoAtual == ModoApp::Modo2D) aplicarEscala2D(0.9);
                    else aplicarEscala3D(0.9);
                }

                // Rotacao 2D (, e .)
                if (tecla->code == sf::Keyboard::Key::Comma)  aplicarRotacao2D(-15.0);
                if (tecla->code == sf::Keyboard::Key::Period) aplicarRotacao2D(15.0);

                // Reflexoes (R e T)
                if (tecla->code == sf::Keyboard::Key::R) aplicarReflexaoX2D();
                if (tecla->code == sf::Keyboard::Key::T) aplicarReflexaoY2D();

                // Reset (Q)
                if (tecla->code == sf::Keyboard::Key::Q)
                {
                    if (modoAtual == ModoApp::Modo2D) resetarFigura2D();
                    else resetar3D();
                }

                // Movimento por setas no 2D
                if (tecla->code == sf::Keyboard::Key::Up)    transladarFigura2D(0.0, -15.0);
                if (tecla->code == sf::Keyboard::Key::Down)  transladarFigura2D(0.0, 15.0);
                if (tecla->code == sf::Keyboard::Key::Left)  transladarFigura2D(-15.0, 0.0);
                if (tecla->code == sf::Keyboard::Key::Right) transladarFigura2D(15.0, 0.0);

                // Rotações do Cubo 3D
                if (tecla->code == sf::Keyboard::Key::W) aplicarRotacaoX3D(-15.0);
                if (tecla->code == sf::Keyboard::Key::S) aplicarRotacaoX3D(15.0);
                if (tecla->code == sf::Keyboard::Key::A) aplicarRotacaoY3D(-15.0);
                if (tecla->code == sf::Keyboard::Key::D) aplicarRotacaoY3D(15.0);
                if (tecla->code == sf::Keyboard::Key::Z) aplicarRotacaoZ3D(-15.0);
                if (tecla->code == sf::Keyboard::Key::X) aplicarRotacaoZ3D(15.0);

                // Selecao de figura (1 a 5)
                if (tecla->code == sf::Keyboard::Key::Num1) executarAcaoBotao("fig_quad");
                if (tecla->code == sf::Keyboard::Key::Num2) executarAcaoBotao("fig_ret");
                if (tecla->code == sf::Keyboard::Key::Num3) executarAcaoBotao("fig_tri");
                if (tecla->code == sf::Keyboard::Key::Num4) executarAcaoBotao("fig_circ");
                if (tecla->code == sf::Keyboard::Key::Num5) executarAcaoBotao("fig_grade");
            }
        }
    }
}

void App::tratarDigitacaoTexto(char32_t unicode)
{
    if (campoMatrizFocado < 0) return;

    std::string* campo = nullptr;
    if (campoMatrizFocado == 0) campo = &strMatrizA;
    else if (campoMatrizFocado == 1) campo = &strMatrizB;
    else if (campoMatrizFocado == 2) campo = &strMatrizC;
    else if (campoMatrizFocado == 3) campo = &strMatrizD;

    if (!campo) return;

    // Backspace: apaga ultimo caractere
    if (unicode == 8)
    {
        if (!campo->empty()) campo->pop_back();
    }
    // Enter: desativa foco e aplica a matriz
    else if (unicode == 13)
    {
        campoMatrizFocado = -1;
        executarAcaoBotao("btn_aplicar_matriz");
    }
    // Digitos, ponto e sinal de menos
    else if ((unicode >= '0' && unicode <= '9') || unicode == '.' || unicode == '-')
    {
        if (campo->size() < 6)
        {
            campo->push_back(static_cast<char>(unicode));
        }
    }

    // Atualiza o texto visual das celulas
    for (auto& b : botoes)
    {
        if (b.id == "cell_a") b.texto = "a: " + strMatrizA;
        if (b.id == "cell_b") b.texto = "b: " + strMatrizB;
        if (b.id == "cell_c") b.texto = "c: " + strMatrizC;
        if (b.id == "cell_d") b.texto = "d: " + strMatrizD;
    }
}

void App::tratarCliqueMouse(const sf::Vector2i& pos)
{
    // Se o clique foi no painel lateral
    if (pos.x < static_cast<int>(LARGURA_PAINEL))
    {
        sf::Vector2f ponto(static_cast<float>(pos.x), static_cast<float>(pos.y));
        bool clicouEmCampo = false;

        for (const auto& btn : botoes)
        {
            bool visivel = false;
            if (btn.id.rfind("tab_", 0) == 0) visivel = true;
            else if (modoAtual == ModoApp::Modo2D && btn.id.find("3") == std::string::npos && btn.id != "auto_spin") visivel = true;
            else if (modoAtual == ModoApp::Modo3D && (btn.id.find("3") != std::string::npos || btn.id == "auto_spin")) visivel = true;

            if (visivel && btn.bounds.contains(ponto))
            {
                if (btn.id == "cell_a") { campoMatrizFocado = 0; clicouEmCampo = true; }
                else if (btn.id == "cell_b") { campoMatrizFocado = 1; clicouEmCampo = true; }
                else if (btn.id == "cell_c") { campoMatrizFocado = 2; clicouEmCampo = true; }
                else if (btn.id == "cell_d") { campoMatrizFocado = 3; clicouEmCampo = true; }

                executarAcaoBotao(btn.id);
                break;
            }
        }

        if (!clicouEmCampo && campoMatrizFocado >= 0)
        {
            // Clicou fora dos campos de texto, tira o foco
            campoMatrizFocado = -1;
        }
    }
    else
    {
        // Clique no canvas: inicia arrasto da figura
        campoMatrizFocado = -1;
        arrastandoMouse = true;
        ultimaPosMouse = pos;
    }
}

void App::tratarMovimentoMouse(const sf::Vector2i& pos)
{
    sf::Vector2f ponto(static_cast<float>(pos.x), static_cast<float>(pos.y));

    for (auto& btn : botoes)
    {
        btn.hover = btn.bounds.contains(ponto);
    }

    if (arrastandoMouse)
    {
        float dx = static_cast<float>(pos.x - ultimaPosMouse.x);
        float dy = static_cast<float>(pos.y - ultimaPosMouse.y);

        if (modoAtual == ModoApp::Modo2D)
        {
            transladarFigura2D(dx, dy);
        }
        else
        {
            aplicarRotacaoY3D(dx * 0.5);
            aplicarRotacaoX3D(dy * 0.5);
        }
        ultimaPosMouse = pos;
    }
}

void App::tratarSoltarMouse()
{
    arrastandoMouse = false;
}

void App::executarAcaoBotao(const std::string& id)
{
    // Abas
    if (id == "tab_2d")
    {
        modoAtual = ModoApp::Modo2D;
        for (auto& b : botoes) {
            if (b.id == "tab_2d") b.ativo = true;
            if (b.id == "tab_3d") b.ativo = false;
        }
        return;
    }
    if (id == "tab_3d")
    {
        modoAtual = ModoApp::Modo3D;
        for (auto& b : botoes) {
            if (b.id == "tab_3d") b.ativo = true;
            if (b.id == "tab_2d") b.ativo = false;
        }
        return;
    }

    // BOTOES DE LIGAR/DESLIGAR E SELECIONAR FIGURAS
    if (id == "fig_quad")
    {
        mostrarQuadrado = !mostrarQuadrado;
        figuraSelecionada = TipoFigura::Quadrado;
    }
    else if (id == "fig_ret")
    {
        mostrarRetangulo = !mostrarRetangulo;
        figuraSelecionada = TipoFigura::Retangulo;
    }
    else if (id == "fig_tri")
    {
        mostrarTriangulo = !mostrarTriangulo;
        figuraSelecionada = TipoFigura::Triangulo;
    }
    else if (id == "fig_circ")
    {
        mostrarCirculo = !mostrarCirculo;
        figuraSelecionada = TipoFigura::Circulo;
    }
    else if (id == "fig_grade")
    {
        mostrarGrade = !mostrarGrade;
        figuraSelecionada = TipoFigura::Grade;
    }

    // Atualiza texto dos botoes de figura com indicador [X] ou [ ]
    for (auto& b : botoes)
    {
        if (b.id == "fig_quad")  { b.ativo = (figuraSelecionada == TipoFigura::Quadrado);  b.texto = (mostrarQuadrado ? "[X] Quad" : "[ ] Quad"); }
        if (b.id == "fig_ret")   { b.ativo = (figuraSelecionada == TipoFigura::Retangulo); b.texto = (mostrarRetangulo ? "[X] Ret" : "[ ] Ret"); }
        if (b.id == "fig_tri")   { b.ativo = (figuraSelecionada == TipoFigura::Triangulo); b.texto = (mostrarTriangulo ? "[X] Tri" : "[ ] Tri"); }
        if (b.id == "fig_circ")  { b.ativo = (figuraSelecionada == TipoFigura::Circulo);   b.texto = (mostrarCirculo ? "[X] Circulo" : "[ ] Circulo"); }
        if (b.id == "fig_grade") { b.ativo = (figuraSelecionada == TipoFigura::Grade);     b.texto = (mostrarGrade ? "[X] Grade" : "[ ] Grade"); }
    }

    // APLICAR MATRIZ DIGITADA PELO USUARIO
    if (id == "btn_aplicar_matriz")
    {
        double a = 1.0, b = 0.0, c = 0.0, d = 1.0;
        try { if (!strMatrizA.empty()) a = std::stod(strMatrizA); } catch (...) {}
        try { if (!strMatrizB.empty()) b = std::stod(strMatrizB); } catch (...) {}
        try { if (!strMatrizC.empty()) c = std::stod(strMatrizC); } catch (...) {}
        try { if (!strMatrizD.empty()) d = std::stod(strMatrizD); } catch (...) {}

        aplicarMatrizManual(a, b, c, d);
        return;
    }

    // Digitar matriz no terminal
    if (id == "btn_console_matriz")
    {
        std::cout << "\n=============================================\n";
        std::cout << " Digite os 4 valores da matriz 2x2 (a b c d): \n";
        std::cout << " Exemplo: 1.5 0.0 0.0 1.5 (escala de 1.5)\n";
        std::cout << " Entrada: ";
        double a = 1.0, b = 0.0, c = 0.0, d = 1.0;
        if (std::cin >> a >> b >> c >> d)
        {
            strMatrizA = std::to_string(a);
            strMatrizB = std::to_string(b);
            strMatrizC = std::to_string(c);
            strMatrizD = std::to_string(d);
            aplicarMatrizManual(a, b, c, d);
            std::cout << " Matriz aplicada com sucesso!\n";
        }
        return;
    }

    // Presets de Álgebra Linear
    if (id == "pre_id")    { strMatrizA = "1.0"; strMatrizB = "0.0"; strMatrizC = "0.0"; strMatrizD = "1.0"; aplicarMatrizManual(1, 0, 0, 1); }
    if (id == "pre_reflx") { strMatrizA = "1.0"; strMatrizB = "0.0"; strMatrizC = "0.0"; strMatrizD = "-1.0"; aplicarMatrizManual(1, 0, 0, -1); }
    if (id == "pre_refly") { strMatrizA = "-1.0"; strMatrizB = "0.0"; strMatrizC = "0.0"; strMatrizD = "1.0"; aplicarMatrizManual(-1, 0, 0, 1); }
    if (id == "pre_shear") { strMatrizA = "1.0"; strMatrizB = "0.5"; strMatrizC = "0.0"; strMatrizD = "1.0"; aplicarMatrizManual(1, 0.5, 0, 1); }

    // Transformacoes 2D rapidas
    if (id == "scale_up")   aplicarEscala2D(1.1);
    if (id == "scale_down") aplicarEscala2D(0.9);
    if (id == "rot_pos")    aplicarRotacao2D(15.0);
    if (id == "rot_neg")    aplicarRotacao2D(-15.0);
    if (id == "refl_x")     aplicarReflexaoX2D();
    if (id == "refl_y")     aplicarReflexaoY2D();
    if (id == "refl_orig")  aplicarReflexaoOrigem2D();

    if (id == "move_up")    transladarFigura2D(0.0, -20.0);
    if (id == "move_down")  transladarFigura2D(0.0, 20.0);
    if (id == "move_left")  transladarFigura2D(-20.0, 0.0);
    if (id == "move_right") transladarFigura2D(20.0, 0.0);
    if (id == "move_center") resetarFigura2D();
    if (id == "reset_2d")   resetarFigura2D();

    // Botoes do Modo 3D
    if (id == "rot3_xm") aplicarRotacaoX3D(-15.0);
    if (id == "rot3_xp") aplicarRotacaoX3D(15.0);
    if (id == "rot3_ym") aplicarRotacaoY3D(-15.0);
    if (id == "rot3_yp") aplicarRotacaoY3D(15.0);
    if (id == "rot3_zm") aplicarRotacaoZ3D(-15.0);
    if (id == "rot3_zp") aplicarRotacaoZ3D(15.0);
    if (id == "scale3_up")   aplicarEscala3D(1.1);
    if (id == "scale3_down") aplicarEscala3D(0.9);

    if (id == "auto_spin")
    {
        autoGiro3D = !autoGiro3D;
        for (auto& b : botoes) {
            if (b.id == "auto_spin") {
                b.ativo = autoGiro3D;
                b.texto = autoGiro3D ? "⏸ Pausar Giro" : "▶ Auto-Giro: OFF";
            }
        }
    }
    if (id == "reset_3d") resetar3D();
}

void App::aplicarMatrizManual(double a, double b, double c, double d)
{
    Matriz m(a, b, c, d);
    matrizAcumulada2D = m * matrizAcumulada2D;

    switch (figuraSelecionada)
    {
        case TipoFigura::Quadrado:  quadrado.aplicarMatrizCentrada(m); break;
        case TipoFigura::Retangulo: retangulo.aplicarMatrizCentrada(m); break;
        case TipoFigura::Triangulo: triangulo.aplicarMatrizCentrada(m); break;
        case TipoFigura::Circulo:   circulo.redimensionar(circulo.getRaio() * (std::sqrt(std::abs(a * d - b * c)) - 1.0)); break;
        case TipoFigura::Grade:     grade.aplicarMatriz(m); break;
    }
}

void App::aplicarEscala2D(double fator)
{
    Matriz m = Transformacao::escala(fator);
    matrizAcumulada2D = m * matrizAcumulada2D;

    switch (figuraSelecionada)
    {
        case TipoFigura::Quadrado:  quadrado.aplicarMatrizCentrada(m); break;
        case TipoFigura::Retangulo: retangulo.aplicarMatrizCentrada(m); break;
        case TipoFigura::Triangulo: triangulo.aplicarMatrizCentrada(m); break;
        case TipoFigura::Circulo:   circulo.redimensionar(circulo.getRaio() * (fator - 1.0)); break;
        case TipoFigura::Grade:     grade.aplicarMatriz(m); break;
    }
}

void App::aplicarRotacao2D(double angulo)
{
    Matriz m = Transformacao::rotacao(angulo);
    matrizAcumulada2D = m * matrizAcumulada2D;

    switch (figuraSelecionada)
    {
        case TipoFigura::Quadrado:  quadrado.aplicarMatrizCentrada(m); break;
        case TipoFigura::Retangulo: retangulo.aplicarMatrizCentrada(m); break;
        case TipoFigura::Triangulo: triangulo.aplicarMatrizCentrada(m); break;
        case TipoFigura::Circulo:   break;
        case TipoFigura::Grade:     grade.aplicarMatriz(m); break;
    }
}

void App::aplicarReflexaoX2D()
{
    Matriz m = Transformacao::reflexaoX();
    matrizAcumulada2D = m * matrizAcumulada2D;

    switch (figuraSelecionada)
    {
        case TipoFigura::Quadrado:  quadrado.aplicarMatrizCentrada(m); break;
        case TipoFigura::Retangulo: retangulo.aplicarMatrizCentrada(m); break;
        case TipoFigura::Triangulo: triangulo.aplicarMatrizCentrada(m); break;
        case TipoFigura::Circulo:   break;
        case TipoFigura::Grade:     grade.aplicarMatriz(m); break;
    }
}

void App::aplicarReflexaoY2D()
{
    Matriz m = Transformacao::reflexaoY();
    matrizAcumulada2D = m * matrizAcumulada2D;

    switch (figuraSelecionada)
    {
        case TipoFigura::Quadrado:  quadrado.aplicarMatrizCentrada(m); break;
        case TipoFigura::Retangulo: retangulo.aplicarMatrizCentrada(m); break;
        case TipoFigura::Triangulo: triangulo.aplicarMatrizCentrada(m); break;
        case TipoFigura::Circulo:   break;
        case TipoFigura::Grade:     grade.aplicarMatriz(m); break;
    }
}

void App::aplicarReflexaoOrigem2D()
{
    Matriz m = Transformacao::reflexaoOrigem();
    matrizAcumulada2D = m * matrizAcumulada2D;

    switch (figuraSelecionada)
    {
        case TipoFigura::Quadrado:  quadrado.aplicarMatrizCentrada(m); break;
        case TipoFigura::Retangulo: retangulo.aplicarMatrizCentrada(m); break;
        case TipoFigura::Triangulo: triangulo.aplicarMatrizCentrada(m); break;
        case TipoFigura::Circulo:   break;
        case TipoFigura::Grade:     grade.aplicarMatriz(m); break;
    }
}

void App::transladarFigura2D(double dx, double dy)
{
    switch (figuraSelecionada)
    {
        case TipoFigura::Quadrado:  quadrado.transladar(dx, dy); break;
        case TipoFigura::Retangulo: retangulo.mover(dx, dy); break;
        case TipoFigura::Triangulo: triangulo.transladar(dx, dy); break;
        case TipoFigura::Circulo:
            circulo.mover(dx, dy);
            circulo.limitarA(LARGURA_JANELA, ALTURA_JANELA);
            break;
        case TipoFigura::Grade: grade.transladar(dx, dy); break;
    }
}

void App::resetarFigura2D()
{
    matrizAcumulada2D = Matriz::identidade();
    strMatrizA = "1.0";
    strMatrizB = "0.0";
    strMatrizC = "0.0";
    strMatrizD = "1.0";

    for (auto& b : botoes)
    {
        if (b.id == "cell_a") b.texto = "a: 1.0";
        if (b.id == "cell_b") b.texto = "b: 0.0";
        if (b.id == "cell_c") b.texto = "c: 0.0";
        if (b.id == "cell_d") b.texto = "d: 1.0";
    }

    quadrado = Quadrado(580.0, 200.0, 90.0);
    retangulo.resetar(520.0, 360.0, 130.0, 75.0);
    triangulo = Triangulo(750.0, 140.0, 690.0, 240.0, 810.0, 240.0);
    circulo.resetar(750.0, 480.0, 65.0);
    grade.resetar();
}

void App::aplicarRotacaoX3D(double angulo)
{
    Matriz3 m = Transformacao3D::rotacaoX(angulo);
    cubo.aplicarMatriz(m);
    matrizAcumulada3D = m * matrizAcumulada3D;
}

void App::aplicarRotacaoY3D(double angulo)
{
    Matriz3 m = Transformacao3D::rotacaoY(angulo);
    cubo.aplicarMatriz(m);
    matrizAcumulada3D = m * matrizAcumulada3D;
}

void App::aplicarRotacaoZ3D(double angulo)
{
    Matriz3 m = Transformacao3D::rotacaoZ(angulo);
    cubo.aplicarMatriz(m);
    matrizAcumulada3D = m * matrizAcumulada3D;
}

void App::aplicarEscala3D(double fator)
{
    Matriz3 m = Transformacao3D::escala(fator);
    cubo.aplicarMatriz(m);
    matrizAcumulada3D = m * matrizAcumulada3D;
}

void App::resetar3D()
{
    cubo.resetar(160.0);
    matrizAcumulada3D = Matriz3::identidade();
}

void App::update()
{
    if (modoAtual == ModoApp::Modo3D && autoGiro3D)
    {
        aplicarRotacaoY3D(1.2);
    }
}

sf::Vector2f App::projetar(const Ponto3D& p) const
{
    double z = p.getZ() + distanciaCamera;
    if (z < 1.0) z = 1.0;

    double fator = distanciaCamera / z;

    float x = static_cast<float>(p.getX() * fator + 750.0);
    float y = static_cast<float>(-p.getY() * fator + 350.0);

    return sf::Vector2f(x, y);
}

void App::desenharTexto(const std::string& str, float x, float y, unsigned int tam, const sf::Color& cor, bool /*negrito*/)
{
    if (!fonteCarregada) return;
    sf::Text texto(fonte, str, tam);
    texto.setFillColor(cor);
    texto.setPosition({ x, y });
    window.draw(texto);
}

void App::desenharFigura(const Figura& figura, const sf::Color& corPreenchimento, const sf::Color& corBorda, float espessuraBorda)
{
    const auto& pontos = figura.getPontos();
    if (pontos.empty()) return;

    sf::ConvexShape forma;
    forma.setPointCount(static_cast<std::size_t>(pontos.size()));

    for (std::size_t i = 0; i < pontos.size(); ++i)
    {
        forma.setPoint(i, sf::Vector2f(
            static_cast<float>(pontos[i].getX()),
            static_cast<float>(pontos[i].getY())
        ));
    }

    forma.setFillColor(corPreenchimento);
    forma.setOutlineColor(corBorda);
    forma.setOutlineThickness(espessuraBorda);
    window.draw(forma);

    // Desenha pontinhos nos vertices
    for (const auto& p : pontos)
    {
        sf::CircleShape vert(3.5f);
        vert.setOrigin({ 3.5f, 3.5f });
        vert.setPosition({ static_cast<float>(p.getX()), static_cast<float>(p.getY()) });
        vert.setFillColor(sf::Color::White);
        window.draw(vert);
    }
}

void App::desenharQuadrado()
{
    bool ativo = (figuraSelecionada == TipoFigura::Quadrado);
    sf::Color fill = ativo ? sf::Color(16, 185, 129, 210) : sf::Color(16, 185, 129, 80);
    sf::Color border = ativo ? sf::Color::White : sf::Color(16, 185, 129, 160);
    desenharFigura(quadrado, fill, border, ativo ? 2.5f : 1.2f);
}

void App::desenharRetangulo()
{
    bool ativo = (figuraSelecionada == TipoFigura::Retangulo);
    sf::Color fill = ativo ? sf::Color(239, 68, 68, 210) : sf::Color(239, 68, 68, 80);
    sf::Color border = ativo ? sf::Color::White : sf::Color(239, 68, 68, 160);
    desenharFigura(retangulo, fill, border, ativo ? 2.5f : 1.2f);
}

void App::desenharTriangulo()
{
    bool ativo = (figuraSelecionada == TipoFigura::Triangulo);
    sf::Color fill = ativo ? sf::Color(245, 158, 11, 210) : sf::Color(245, 158, 11, 80);
    sf::Color border = ativo ? sf::Color::White : sf::Color(245, 158, 11, 160);
    desenharFigura(triangulo, fill, border, ativo ? 2.5f : 1.2f);
}

void App::desenharCirculo()
{
    bool ativo = (figuraSelecionada == TipoFigura::Circulo);
    float raio = static_cast<float>(circulo.getRaio());

    sf::CircleShape forma(raio);
    forma.setOrigin({ raio, raio });
    forma.setPosition({
        static_cast<float>(circulo.getCentroX()),
        static_cast<float>(circulo.getCentroY())
    });

    forma.setFillColor(ativo ? sf::Color(14, 165, 233, 190) : sf::Color(14, 165, 233, 80));
    forma.setOutlineColor(ativo ? sf::Color::White : sf::Color(14, 165, 233, 160));
    forma.setOutlineThickness(ativo ? 2.5f : 1.2f);
    window.draw(forma);

    sf::CircleShape centro(3.5f);
    centro.setOrigin({ 3.5f, 3.5f });
    centro.setPosition(forma.getPosition());
    centro.setFillColor(sf::Color::White);
    window.draw(centro);
}

void App::desenharGrade()
{
    bool ativo = (figuraSelecionada == TipoFigura::Grade);
    sf::Color fill = ativo ? sf::Color(168, 85, 247, 180) : sf::Color(168, 85, 247, 70);
    sf::Color border = ativo ? sf::Color::White : sf::Color(168, 85, 247, 140);

    for (const auto& q : grade.getQuadrados())
    {
        desenharFigura(q, fill, border, ativo ? 1.5f : 1.0f);
    }
}

void App::desenharCubo()
{
    const auto& vertices = cubo.getVertices();
    const auto& arestas = cubo.getArestas();

    // Eixos 3D
    const double tamEixo = 140.0;
    sf::Vector2f origProj = projetar(Ponto3D(0, 0, 0));
    sf::Vector2f xProj = projetar(matrizAcumulada3D.aplicar(Ponto3D(tamEixo, 0, 0)));
    sf::Vector2f yProj = projetar(matrizAcumulada3D.aplicar(Ponto3D(0, tamEixo, 0)));
    sf::Vector2f zProj = projetar(matrizAcumulada3D.aplicar(Ponto3D(0, 0, tamEixo)));

    auto desenharEixo = [&](sf::Vector2f p1, sf::Vector2f p2, sf::Color cor, const std::string& rotulo) {
        sf::VertexArray l(sf::PrimitiveType::Lines, 2);
        l[0].position = p1; l[0].color = cor;
        l[1].position = p2; l[1].color = cor;
        window.draw(l);
        desenharTexto(rotulo, p2.x + 4.f, p2.y - 8.f, 13, cor, true);
    };

    desenharEixo(origProj, xProj, sf::Color(239, 68, 68), "X");
    desenharEixo(origProj, yProj, sf::Color(34, 197, 94), "Y");
    desenharEixo(origProj, zProj, sf::Color(59, 130, 246), "Z");

    // Arestas do cubo
    for (const auto& aresta : arestas)
    {
        sf::Vector2f p1 = projetar(vertices[aresta.first]);
        sf::Vector2f p2 = projetar(vertices[aresta.second]);

        sf::VertexArray linha(sf::PrimitiveType::Lines, 2);
        linha[0].position = p1;
        linha[0].color = sf::Color(56, 189, 248);
        linha[1].position = p2;
        linha[1].color = sf::Color(56, 189, 248);
        window.draw(linha);
    }

    // Vertices do cubo
    for (const auto& v : vertices)
    {
        sf::Vector2f pos = projetar(v);
        sf::CircleShape ponto(4.5f);
        ponto.setOrigin({ 4.5f, 4.5f });
        ponto.setPosition(pos);
        ponto.setFillColor(sf::Color(245, 158, 11));
        ponto.setOutlineColor(sf::Color::White);
        ponto.setOutlineThickness(1.0f);
        window.draw(ponto);
    }
}

void App::desenharEixosCartesianos()
{
    const float inicioX = LARGURA_PAINEL;
    const float passo = 40.0f;
    sf::Color corGrade(25, 32, 45);

    // Linhas de grade sutis
    for (float x = inicioX; x <= LARGURA_JANELA; x += passo)
    {
        sf::VertexArray l(sf::PrimitiveType::Lines, 2);
        l[0].position = sf::Vector2f(x, 0.f); l[0].color = corGrade;
        l[1].position = sf::Vector2f(x, ALTURA_JANELA); l[1].color = corGrade;
        window.draw(l);
    }
    for (float y = 0.f; y <= ALTURA_JANELA; y += passo)
    {
        sf::VertexArray l(sf::PrimitiveType::Lines, 2);
        l[0].position = sf::Vector2f(inicioX, y); l[0].color = corGrade;
        l[1].position = sf::Vector2f(LARGURA_JANELA, y); l[1].color = corGrade;
        window.draw(l);
    }

    // Eixos X e Y
    float centroX = inicioX + (LARGURA_JANELA - inicioX) / 2.0f;
    float centroY = ALTURA_JANELA / 2.0f;
    sf::Color corEixo(50, 65, 88);

    sf::VertexArray eixoX(sf::PrimitiveType::Lines, 2);
    eixoX[0].position = sf::Vector2f(inicioX, centroY); eixoX[0].color = corEixo;
    eixoX[1].position = sf::Vector2f(LARGURA_JANELA, centroY); eixoX[1].color = corEixo;
    window.draw(eixoX);

    sf::VertexArray eixoY(sf::PrimitiveType::Lines, 2);
    eixoY[0].position = sf::Vector2f(centroX, 0.f); eixoY[0].color = corEixo;
    eixoY[1].position = sf::Vector2f(centroX, ALTURA_JANELA); eixoY[1].color = corEixo;
    window.draw(eixoY);

    desenharTexto("+X", LARGURA_JANELA - 28.f, centroY - 20.f, 12, sf::Color(130, 145, 170));
    desenharTexto("+Y", centroX + 8.f, 8.f, 12, sf::Color(130, 145, 170));
    desenharTexto("(0,0)", centroX + 6.f, centroY + 4.f, 11, sf::Color(100, 115, 140));
}

void App::renderizarCanvas()
{
    desenharEixosCartesianos();

    if (modoAtual == ModoApp::Modo2D)
    {
        // Desenha apenas as figuras que o usuario escolheu ligar
        if (mostrarQuadrado)  desenharQuadrado();
        if (mostrarRetangulo) desenharRetangulo();
        if (mostrarTriangulo) desenharTriangulo();
        if (mostrarCirculo)   desenharCirculo();
        if (mostrarGrade)     desenharGrade();
    }
    else
    {
        desenharCubo();
    }
}

void App::renderizarPainelUI()
{
    // Fundo do painel
    sf::RectangleShape painelBg(sf::Vector2f(LARGURA_PAINEL, ALTURA_JANELA));
    painelBg.setFillColor(sf::Color(20, 26, 35));
    painelBg.setOutlineColor(sf::Color(45, 58, 78));
    painelBg.setOutlineThickness(1.0f);
    window.draw(painelBg);

    // Titulo
    desenharTexto("PAINEL DE CONTROLE", 15.f, 12.f, 15, sf::Color(56, 189, 248), true);
    desenharTexto("Trabalho de Algebra Linear", 15.f, 29.f, 11, sf::Color(148, 163, 184));

    if (modoAtual == ModoApp::Modo2D)
    {
        desenharTexto("1. FIGURAS (LIGAR / SELECIONAR):", 15.f, 86.f, 11, sf::Color(203, 213, 225));
        desenharTexto("2. DIGITAR MATRIZ (2x2):", 15.f, 170.f, 11, sf::Color(203, 213, 225));
        desenharTexto("3. TRANSFORMACÕES RÁPIDAS:", 15.f, 288.f, 11, sf::Color(203, 213, 225));
        desenharTexto("4. MOVER FIGURA ATIVA:", 15.f, 372.f, 11, sf::Color(203, 213, 225));
    }
    else
    {
        desenharTexto("1. ROTAÇÃO DO CUBO NOS EIXOS:", 15.f, 95.f, 11, sf::Color(203, 213, 225));
        desenharTexto("2. ESCALA 3D:", 15.f, 218.f, 11, sf::Color(203, 213, 225));
        desenharTexto("3. GIRO CONTÍNUO & RESET:", 15.f, 268.f, 11, sf::Color(203, 213, 225));
    }

    // Renderiza botoes
    for (const auto& btn : botoes)
    {
        bool visivel = false;
        if (btn.id.rfind("tab_", 0) == 0) visivel = true;
        else if (modoAtual == ModoApp::Modo2D && btn.id.find("3") == std::string::npos && btn.id != "auto_spin") visivel = true;
        else if (modoAtual == ModoApp::Modo3D && (btn.id.find("3") != std::string::npos || btn.id == "auto_spin")) visivel = true;

        if (!visivel) continue;

        sf::RectangleShape box(btn.bounds.size);
        box.setPosition(btn.bounds.position);

        sf::Color corFundo = btn.corNormal;
        if (btn.ativo) corFundo = btn.corAtivo;
        else if (btn.hover) corFundo = btn.corHover;

        // Se for um campo de digitacao focado
        if ((btn.id == "cell_a" && campoMatrizFocado == 0) ||
            (btn.id == "cell_b" && campoMatrizFocado == 1) ||
            (btn.id == "cell_c" && campoMatrizFocado == 2) ||
            (btn.id == "cell_d" && campoMatrizFocado == 3))
        {
            corFundo = sf::Color(40, 70, 110);
            box.setOutlineColor(sf::Color(56, 189, 248));
            box.setOutlineThickness(2.0f);
        }
        else
        {
            box.setOutlineColor(btn.ativo ? sf::Color::White : (btn.hover ? sf::Color(100, 140, 200) : sf::Color(50, 65, 85)));
            box.setOutlineThickness(btn.ativo ? 1.5f : 1.0f);
        }

        box.setFillColor(corFundo);
        window.draw(box);

        float txtX = btn.bounds.position.x + 6.f;
        float txtY = btn.bounds.position.y + (btn.bounds.size.y - 14.f) / 2.0f;
        desenharTexto(btn.texto, txtX, txtY, 11, sf::Color::White);
    }

    // Cartao da Matriz Acumulada
    sf::RectangleShape matrixCard(sf::Vector2f(290.f, 95.f));
    matrixCard.setPosition({ 15.f, 520.f });
    matrixCard.setFillColor(sf::Color(14, 18, 26));
    matrixCard.setOutlineColor(sf::Color(45, 58, 78));
    matrixCard.setOutlineThickness(1.0f);
    window.draw(matrixCard);

    if (modoAtual == ModoApp::Modo2D)
    {
        desenharTexto("Matriz Acumulada da Figura Ativa:", 25.f, 526.f, 11, sf::Color(56, 189, 248));
        std::string l1 = "| " + formatarNumero(matrizAcumulada2D.getA()) + "  " + formatarNumero(matrizAcumulada2D.getB()) + " |";
        std::string l2 = "| " + formatarNumero(matrizAcumulada2D.getC()) + "  " + formatarNumero(matrizAcumulada2D.getD()) + " |";
        desenharTexto(l1, 40.f, 545.f, 12, sf::Color::White);
        desenharTexto(l2, 40.f, 563.f, 12, sf::Color::White);

        double det = matrizAcumulada2D.determinante();
        std::string detStr = "det(M) = " + formatarNumero(det) + (det < 0.0 ? " (Inverte orientacao)" : " (Preserva orientacao)");
        desenharTexto(detStr, 25.f, 588.f, 10, (std::abs(det) < 0.001) ? sf::Color(239, 68, 68) : sf::Color(148, 163, 184));
    }
    else
    {
        desenharTexto("Matriz de Rotação R (3x3):", 25.f, 526.f, 11, sf::Color(56, 189, 248));
        std::string l1 = "| " + formatarNumero(matrizAcumulada3D.get(0,0)) + " " + formatarNumero(matrizAcumulada3D.get(0,1)) + " " + formatarNumero(matrizAcumulada3D.get(0,2)) + " |";
        std::string l2 = "| " + formatarNumero(matrizAcumulada3D.get(1,0)) + " " + formatarNumero(matrizAcumulada3D.get(1,1)) + " " + formatarNumero(matrizAcumulada3D.get(1,2)) + " |";
        std::string l3 = "| " + formatarNumero(matrizAcumulada3D.get(2,0)) + " " + formatarNumero(matrizAcumulada3D.get(2,1)) + " " + formatarNumero(matrizAcumulada3D.get(2,2)) + " |";
        desenharTexto(l1, 25.f, 544.f, 10, sf::Color::White);
        desenharTexto(l2, 25.f, 560.f, 10, sf::Color::White);
        desenharTexto(l3, 25.f, 576.f, 10, sf::Color::White);
        desenharTexto("v' = s . R . v", 25.f, 595.f, 10, sf::Color(148, 163, 184));
    }

    desenharTexto("Arraste com o mouse no desenho para mover / orbitar.", 15.f, 630.f, 10, sf::Color(115, 130, 155));
    desenharTexto("Dica: Clique nas caixas a, b, c, d para digitar valores.", 15.f, 650.f, 10, sf::Color(115, 130, 155));
}

void App::render()
{
    window.clear(sf::Color(15, 18, 25));

    renderizarCanvas();
    renderizarPainelUI();

    window.display();
}
