#pragma once

#include "Ponto.hpp"

class Matriz
{
public:
    Matriz(double a, double b, double c, double d);

    Ponto aplicar(const Ponto& ponto) const;

private:
    double a;
    double b;
    double c;
    double d;
};