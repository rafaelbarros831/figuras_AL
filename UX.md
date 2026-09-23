# Integração da Interface Gráfica no Projeto "Transformação de Figuras"

Esta documentação descreve a adição de um painel de controle e botões (*GUI*) à arquitetura do projeto existente em C++20 com SFML 3.1, respeitando o ciclo da aplicação: **`processEvents() -> update() -> render()`**.

---

## 📁 Estrutura do Projeto Atualizada

A interface é adicionada como um novo módulo (`UI.hpp` e `UI.cpp`), sem alterar a estrutura das tuas classes geométricas e de matrizes existentes:

```text
figuras_AL/
│
└── projeto_configurado/
    ├── include/
    │   ├── App.hpp
    │   ├── Figura.hpp
    │   ├── Transformacao.hpp
    │   ├── Triangulo.hpp / Quadrado.hpp / Retangulo.hpp
    │   ├── Matriz.hpp / Ponto.hpp
    │   └── UI.hpp                 <-- [NOVO] Declaração da Interface Gráfica
    │
    ├── src/
    │   ├── App.cpp
    │   ├── Figura.cpp
    │   ├── Transformacao.cpp
    │   ├── Triangulo.cpp / Quadrado.cpp / Retangulo.cpp
    │   ├── Matriz.cpp / Ponto.cpp
    │   └── UI.cpp                 <-- [NOVO] Implementação dos Botões e Cliques
    │
    └── projeto_configurado.cpp

  ```
  🛠️ 1. Cabeçalho da Interface (include/UI.hpp)
Define as ações disparadas pelos botões e a estrutura da classe responsável por desenhar o painel lateral e capturar eventos do rato.

``` cpp
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <optional>

// Lista de transformações acionadas pela interface
enum class AcaoTransformacao {
    Nenhuma,
    EscalaAumentar,
    EscalaDiminuir,
    RotacionarHorario,
    RotacionarAntiHorario,
    RefletirX,
    RefletirY
};

struct Botao {
    sf::RectangleShape retangulo;
    sf::Text texto;
    AcaoTransformacao acao;
};

class UI {
public:
    UI();

    // Processa os eventos de clique do rato
    void processarEvento(const std::optional<sf::Event>& evento, const sf::RenderWindow& janela);

    // Retorna a ação selecionada pelo utilizador e reseta para 'Nenhuma'
    AcaoTransformacao obterAcaoE_Resetar();

    // Desenha o painel e os botões na janela
    void renderizar(sf::RenderWindow& janela);

private:
    sf::RectangleShape painelFundo;
    sf::Font fonte;
    std::vector<Botao> botoes;
    AcaoTransformacao acaoPendente = AcaoTransformacao::Nenhuma;

    void criarBotao(float y, const std::string& rotulo, AcaoTransformacao acao);
};
```
💻 2. Implementação da Interface (src/UI.cpp)
Lógica de criação dos botões e verificação de cliques de acordo com a API do SFML 3.1.

``` cpp
#include "UI.hpp"

UI::UI() {
    // Painel lateral à esquerda com 220px de largura
    painelFundo.setSize({220.0f, 600.0f});
    painelFundo.setFillColor(sf::Color(45, 45, 48));

    // Carregamento da fonte (certifica-te de ter um ficheiro .ttf válido na pasta)
    if (fonte.openFromFile("arial.ttf")) {
        criarBotao(30.0f,  "Escala: +10%",  AcaoTransformacao::EscalaAumentar);
        criarBotao(80.0f,  "Escala: -10%",  AcaoTransformacao::EscalaDiminuir);
        criarBotao(150.0f, "Girar +15 deg", AcaoTransformacao::RotacionarHorario);
        criarBotao(200.0f, "Girar -15 deg", AcaoTransformacao::RotacionarAntiHorario);
        criarBotao(270.0f, "Refletir Eixo X", AcaoTransformacao::RefletirX);
        criarBotao(320.0f, "Refletir Eixo Y", AcaoTransformacao::RefletirY);
    }
}

void UI::criarBotao(float y, const std::string& rotulo, AcaoTransformacao acao) {
    Botao b;
    b.retangulo.setSize({180.0f, 35.0f});
    b.retangulo.setPosition({20.0f, y});
    b.retangulo.setFillColor(sf::Color(70, 70, 80));
    b.retangulo.setOutlineThickness(1.0f);
    b.retangulo.setOutlineColor(sf::Color::White);

    b.texto.setFont(fonte);
    b.texto.setString(rotulo);
    b.texto.setCharacterSize(14);
    b.texto.setFillColor(sf::Color::White);
    b.texto.setPosition({30.0f, y + 8.0f});

    b.acao = acao;
    botoes.push_back(b);
}

void UI::processarEvento(const std::optional<sf::Event>& evento, const sf::RenderWindow& janela) {
    if (!evento) return;

    // SFML 3.1: Tratamento do evento de clique do rato
    if (const auto* mouseBtn = evento->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseBtn->button == sf::Mouse::Button::Left) {
            sf::Vector2f posMouse(static_cast<float>(mouseBtn->position.x), static_cast<float>(mouseBtn->position.y));

            for (const auto& b : botoes) {
                if (b.retangulo.getGlobalBounds().contains(posMouse)) {
                    acaoPendente = b.acao;
                    break;
                }
            }
        }
    }
}

AcaoTransformacao UI::obterAcaoE_Resetar() {
    AcaoTransformacao acao = acaoPendente;
    acaoPendente = AcaoTransformacao::Nenhuma;
    return acao;
}

void UI::renderizar(sf::RenderWindow& janela) {
    janela.draw(painelFundo);
    for (auto& b : botoes) {
        janela.draw(b.retangulo);
        janela.draw(b.texto);
    }
}
```
🔄 3. Conexão no Controladador Principal (App.hpp e App.cpp)
A classe App executa a ponte entre a interface gráfica e a aplicação das matrizes.

include/App.hpp
``` cpp
#pragma once
#include <SFML/Graphics.hpp>
#include "UI.hpp"
#include "Triangulo.hpp"
#include "Transformacao.hpp"

class App {
public:
    App();
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    UI interfaceGrafica;
    Triangulo figura; 
    Transformacao transformador; 
};
src/App.cpp
C++
#include "App.hpp"

App::App() 
    : window(sf::VideoMode({1000, 600}), "Atividade 5 - Transformacao de Figuras"),
      interfaceGrafica() {}

void App::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void App::processEvents() {
    while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        // 1. Processamento da UI
        interfaceGrafica.processarEvento(event, window);
    }
}

void App::update() {
    // 2. Consulta a ação disparada na UI
    AcaoTransformacao acao = interfaceGrafica.obterAcaoE_Resetar();

    // Aplica a operação matricial equivalente
    switch (acao) {
        case AcaoTransformacao::EscalaAumentar:
            transformador.aplicarEscala(figura, 1.1f);
            break;
        case AcaoTransformacao::EscalaDiminuir:
            transformador.aplicarEscala(figura, 0.9f);
            break;
        case AcaoTransformacao::RotacionarHorario:
            transformador.aplicarRotacao(figura, 15.0f);
            break;
        case AcaoTransformacao::RotacionarAntiHorario:
            transformador.aplicarRotacao(figura, -15.0f);
            break;
        case AcaoTransformacao::RefletirX:
            transformador.aplicarReflexaoX(figura);
            break;
        case AcaoTransformacao::RefletirY:
            transformador.aplicarReflexaoY(figura);
            break;
        case AcaoTransformacao::Nenhuma:
            break;
    }
}

void App::render() {
    window.clear(sf::Color(30, 30, 30));

    // 3. Renderização
    figura.desenhar(window);         // Desenha a figura transformada
    interfaceGrafica.renderizar(window); // Desenha o painel lateral por cima

    window.display();
}
```

📊 Fluxo de Execução com a Interface
``` text
[ Rato Clica no Botão ]
              │
              ▼
    processEvents()   ---> Captura posMouse e marca a 'acaoPendente' na UI
              │
              ▼
       update()       ---> Obtém 'acaoPendente', calcula a Matriz e altera a Figura
              │
              ▼
       render()       ---> Desenha a Figura atualizada + Painel da UI na Janela
```
