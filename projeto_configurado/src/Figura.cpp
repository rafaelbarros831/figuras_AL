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

void Figura::transladar(double dx, double dy)
{
	for (auto& ponto : pontos)
	{
		ponto = Ponto(ponto.getX() + dx, ponto.getY() + dy);
	}
}

Ponto Figura::calcularCentro() const
{
	double somaX = 0.0;
	double somaY = 0.0;

	for (const auto& ponto : pontos)
	{
		somaX += ponto.getX();
		somaY += ponto.getY();
	}

	double quantidade = static_cast<double>(pontos.size());

	return Ponto(somaX / quantidade, somaY / quantidade);
}

void Figura::aplicarMatrizCentrada(const Matriz& matriz)
{
	Ponto centro = calcularCentro();

	transladar(-centro.getX(), -centro.getY());
	aplicarMatriz(matriz);
	transladar(centro.getX(), centro.getY());
}