#include "Ponto3D.hpp"

Ponto3D::Ponto3D(double x, double y, double z)
    : x(x), y(y), z(z)
{
}

double Ponto3D::getX() const { return x; }
double Ponto3D::getY() const { return y; }
double Ponto3D::getZ() const { return z; }

void Ponto3D::set(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
