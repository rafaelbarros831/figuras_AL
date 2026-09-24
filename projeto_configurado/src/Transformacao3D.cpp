#include "Transformacao3D.hpp"
#include <cmath>

Matriz3 Transformacao3D::escala(double fator)
{
    return Matriz3(
        fator, 0.0, 0.0,
        0.0, fator, 0.0,
        0.0, 0.0, fator
    );
}

Matriz3 Transformacao3D::rotacaoX(double anguloGraus)
{
    const double PI = 3.14159265358979323846;
    double rad = anguloGraus * PI / 180.0;
    double c = std::cos(rad);
    double s = std::sin(rad);

    return Matriz3(
        1.0, 0.0, 0.0,
        0.0, c, -s,
        0.0, s, c
    );
}

Matriz3 Transformacao3D::rotacaoY(double anguloGraus)
{
    const double PI = 3.14159265358979323846;
    double rad = anguloGraus * PI / 180.0;
    double c = std::cos(rad);
    double s = std::sin(rad);

    return Matriz3(
        c, 0.0, s,
        0.0, 1.0, 0.0,
        -s, 0.0, c
    );
}

Matriz3 Transformacao3D::rotacaoZ(double anguloGraus)
{
    const double PI = 3.14159265358979323846;
    double rad = anguloGraus * PI / 180.0;
    double c = std::cos(rad);
    double s = std::sin(rad);

    return Matriz3(
        c, -s, 0.0,
        s, c, 0.0,
        0.0, 0.0, 1.0
    );
}
