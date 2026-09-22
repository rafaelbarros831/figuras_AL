#include "Transformacao.hpp"
#include <cmath>

Matriz Transformacao::escala(double fator)
{
    return Matriz(
        fator, 0.0,
        0.0, fator
    );
}

Matriz Transformacao::reflexaoX()
{
    return Matriz(
        1.0, 0.0,
        0.0, -1.0
    );
}

Matriz Transformacao::reflexaoY()
{
    return Matriz(
        -1.0, 0.0,
        0.0, 1.0
    );
}

Matriz Transformacao::rotacao(double anguloGraus)
{
    const double PI = 3.14159265358979323846;
    double rad = anguloGraus * PI / 180.0;

    double c = std::cos(rad);
    double s = std::sin(rad);

    return Matriz(
        c, -s,
        s, c
    );
}