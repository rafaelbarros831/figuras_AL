#include "Figura.hpp"

Figura::Figura()
{
}

void Figura::addPonto(const Ponto& ponto)
{
    pontos.push_back(ponto);
}

void Figura::aplicarMatriz(const Matriz& matriz)
{
	for (auto& ponto : pontos)
	{
		ponto = matriz.aplicar(ponto);
	}
}