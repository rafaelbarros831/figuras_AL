#include "Entrada.hpp"

#include <iostream>
#include <limits>

int Entrada::lerInteiro(const char* rotulo)
{
    int valor = 0;

    std::cout << rotulo;

    // Limpa entrada invalida caso o usuario nao digite um numero
    while (!(std::cin >> valor))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Valor invalido. " << rotulo;
    }

    return valor;
}

DimensoesGrade Entrada::lerDimensoesGrade(int maximo)
{
    while (true)
    {
        DimensoesGrade dimensoes;
        dimensoes.linhas = lerInteiro("Linhas: ");
        dimensoes.colunas = lerInteiro("Colunas: ");

        if (dimensoes.linhas > maximo || dimensoes.colunas > maximo)
        {
            std::cout << "O programa nao aceita valores maiores do que " << maximo << ".\n";
        }
        else if (dimensoes.linhas < 1 || dimensoes.colunas < 1)
        {
            std::cout << "O programa precisa de pelo menos 1 linha e 1 coluna.\n";
        }
        else
        {
            return dimensoes;
        }
    }
}
