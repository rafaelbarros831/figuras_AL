#include "Transformacao.hpp"

Matriz Transformacao::escala(double fator)
{
    return Matriz(
        fator, 0.0,
        0.0, fator
    );
}