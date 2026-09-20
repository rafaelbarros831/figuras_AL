#include "Quadrado.hpp"

Quadrado::Quadrado(double x, double y, double tamanho) {
	addPonto(Ponto(x, y));
	addPonto(Ponto(x + tamanho, y));
	addPonto(Ponto(x + tamanho, y + tamanho));
	addPonto(Ponto(x, y + tamanho));
}