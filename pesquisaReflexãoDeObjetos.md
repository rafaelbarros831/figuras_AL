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
