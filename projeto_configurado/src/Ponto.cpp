#include "Ponto.hpp"

Ponto::Ponto(double x, double y)
    : x(x), y(y)
{
}

double Ponto::getX() const
{
    return x;
}

double Ponto::getY() const
{
    return y;
}