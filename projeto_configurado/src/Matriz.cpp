#include "Matriz.hpp"
Matriz::Matriz(double a, double b, double c, double d)
    : a(a), b(b), c(c), d(d)
{
}

Ponto Matriz::aplicar(const Ponto& ponto) const {
	double x = ponto.getX();
	double y = ponto.getY();
	double novoX = a * x + b * y;
	double novoY = c * x + d * y;
	return Ponto(novoX, novoY);
}
