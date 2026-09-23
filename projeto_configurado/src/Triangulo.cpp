#include "Triangulo.hpp"

Triangulo::Triangulo(double a, double b, double c, double d, double e, double f) {
	addPonto(Ponto(a, b));
	addPonto(Ponto(c, d));
	addPonto(Ponto(e, f));
}