# Transformação de Reflexão 2D (Efeito Espelho) em C++

Para transformar uma figura 2D (composta por um conjunto de pontos ou vértices) em uma **reflexão (efeito espelho)** em C++, utilizamos a **Álgebra Linear** por meio de **operações matriciais**.

Na computação gráfica 2D, a reflexão é realizada espelhando os pontos da figura em relação a um eixo (geralmente o Eixo X, Eixo Y ou a Origem $(0,0)$).

---

## 1. O Conceito Matemático (Matrizes de Reflexão)

Para cada ponto $(x, y)$ da figura, aplica-se uma matriz de transformação para obter as novas coordenadas $(x', y')$:

<img width="730" height="440" alt="image" src="https://github.com/user-attachments/assets/901e05e4-4268-4418-a953-223b2f3edc0a" />

---

## 2. Implementação Completa em C++

Abaixo está o exemplo prático em C++ utilizando a representação por vetor de pontos (`std::vector<Ponto>`):

```cpp
#include <iostream>
#include <vector>

// Estrutura para representar um ponto no plano 2D
struct Ponto {
    float x;
    float y;
};

// Função para aplicar a reflexão no Eixo Y (Espelho Horizontal)
std::vector<Ponto> refletirEixoY(const std::vector<Ponto>& figuraOriginal) {
    std::vector<Ponto> figuraRefletida;
    
    // Matriz de Reflexão no Eixo Y:
    // [-1  0]
    // [ 0  1]
    for (const auto& p : figuraOriginal) {
        Ponto novoPonto;
        novoPonto.x = -1.0f * p.x; // Inverte o sinal de X
        novoPonto.y =  1.0f * p.y; // Mantém a coordenada Y
        figuraRefletida.push_back(novoPonto);
    }
    
    return figuraRefletida;
}

int main() {
    // Definindo os vértices de um triângulo simples
    std::vector<Ponto> triangulo = {
        {1.0f, 2.0f},
        {4.0f, 2.0f},
        {2.5f, 5.0f}
    };

    std::cout << "=== Coordenadas Originais ===\n";
    for (const auto& p : triangulo) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }

    // Aplicando a reflexão
    std::vector<Ponto> trianguloEspelhado = refletirEixoY(triangulo);

    std::cout << "\n=== Coordenadas Apos Reflexao (Eixo Y) ===\n";
    for (const auto& p : trianguloEspelhado) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }

    return 0;
}
```
---
<br><br>
## Interface Grafica
```cpp
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

const float PI = 3.14159265359f;

struct Ponto {
    float x, y;
};

// Multiplicação de Ponto 2D por Matriz 2x2
Ponto aplicarMatriz(const Ponto& p, float m00, float m01, float m10, float m11) {
    return {
        (m00 * p.x) + (m01 * p.y),
        (m10 * p.x) + (m11 * p.y)
    };
}

// Transformações
void aplicarEscala(std::vector<Ponto>& vertices, float fator) {
    for (auto& v : vertices) {
        v = aplicarMatriz(v, fator, 0.0f, 0.0f, fator);
    }
}

void aplicarRotacao(std::vector<Ponto>& vertices, float anguloGraus) {
    float rad = anguloGraus * (PI / 180.0f);
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);
    for (auto& v : vertices) {
        v = aplicarMatriz(v, cosA, -sinA, sinA, cosA);
    }
}

void aplicarReflexaoEixoX(std::vector<Ponto>& vertices) {
    for (auto& v : vertices) {
        v = aplicarMatriz(v, 1.0f, 0.0f, 0.0f, -1.0f);
    }
}

void aplicarReflexaoEixoY(std::vector<Ponto>& vertices) {
    for (auto& v : vertices) {
        v = aplicarMatriz(v, -1.0f, 0.0f, 0.0f, 1.0f);
    }
}

int main() {
    // SFML 3.0: Utiliza sf::VideoMode({largura, altura})
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Atividade - SFML 3.0");
    window.setFramerateLimit(60);

    // Vértices do triângulo na origem (0,0)
    std::vector<Ponto> figuraLocal = {
        { 0.0f, -80.0f},
        {-60.0f,  60.0f},
        { 60.0f,  60.0f}
    };

    sf::Vector2f centroTela(400.0f, 300.0f);

    while (window.isOpen()) {
        // SFML 3.0: Tratamento de eventos com std::optional
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                // SFML 3.0: Usa sf::Keyboard::Key::...
                if (keyPressed->code == sf::Keyboard::Key::Up || keyPressed->code == sf::Keyboard::Key::Add) {
                    aplicarEscala(figuraLocal, 1.1f);
                }
                if (keyPressed->code == sf::Keyboard::Key::Down || keyPressed->code == sf::Keyboard::Key::Hyphen) {
                    aplicarEscala(figuraLocal, 0.9f);
                }
                if (keyPressed->code == sf::Keyboard::Key::Left) {
                    aplicarRotacao(figuraLocal, -15.0f);
                }
                if (keyPressed->code == sf::Keyboard::Key::Right) {
                    aplicarRotacao(figuraLocal, 15.0f);
                }
                if (keyPressed->code == sf::Keyboard::Key::H) {
                    aplicarReflexaoEixoY(figuraLocal);
                }
                if (keyPressed->code == sf::Keyboard::Key::V) {
                    aplicarReflexaoEixoX(figuraLocal);
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));

        // Desenhando no SFML 3.0
        sf::VertexArray triangulo(sf::PrimitiveType::Triangles, figuraLocal.size());

        for (std::size_t i = 0; i < figuraLocal.size(); ++i) {
            triangulo[i].position = {
                figuraLocal[i].x + centroTela.x,
                figuraLocal[i].y + centroTela.y
            };
            triangulo[i].color = sf::Color::Yellow;
        }

        window.draw(triangulo);
        window.display();
    }

    return 0;
}
```

