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

Matriz Matriz::operator*(const Matriz& outra) const
{
    return Matriz(
        a * outra.a + b * outra.c,
        a * outra.b + b * outra.d,
        c * outra.a + d * outra.c,
        c * outra.b + d * outra.d
    );
}

Matriz Matriz::identidade()
{
    return Matriz(1.0, 0.0, 0.0, 1.0);
}
