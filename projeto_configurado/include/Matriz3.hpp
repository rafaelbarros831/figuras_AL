#pragma once

#include "Ponto3D.hpp"

class Matriz3
{
public:
    Matriz3();
    Matriz3(
        double m00, double m01, double m02,
        double m10, double m11, double m12,
        double m20, double m21, double m22
    );

    Ponto3D aplicar(const Ponto3D& p) const;
    Matriz3 operator*(const Matriz3& outra) const;

    double get(int linha, int coluna) const { return m[linha][coluna]; }

    static Matriz3 identidade();

private:
    double m[3][3];
};
