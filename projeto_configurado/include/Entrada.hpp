#pragma once

struct DimensoesGrade
{
    int linhas;
    int colunas;
};

// Leitura de dados pelo console.
// Refatoracao do AL do Rafael (figuras_AL-rafael_trbl): a funcao
// Quant() e o while de validacao que ficavam dentro do main()
// foram separados do resto do programa.
class Entrada
{
public:
    // Pergunta linhas e colunas ate receber valores entre 1 e maximo.
    static DimensoesGrade lerDimensoesGrade(int maximo);

private:
    static int lerInteiro(const char* rotulo);
};
