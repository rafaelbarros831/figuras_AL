#pragma once

#include "Ponto.hpp"

class Matriz
{
public:
    Matriz(double a, double b, double c, double d);

    Ponto aplicar(const Ponto& ponto) const;

    double getA() const { return a; }
    double getB() const { return b; }
    double getC() const { return c; }
    double getD() const { return d; }
    double determinante() const { return a * d - b * c; }

    Matriz operator*(const Matriz& outra) const;
    static Matriz identidade();

private:
    double a;
    double b;
    double c;
    double d;
};