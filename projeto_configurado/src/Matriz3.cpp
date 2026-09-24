#include "Matriz3.hpp"

Matriz3::Matriz3()
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m[i][j] = (i == j) ? 1.0 : 0.0;
}

Matriz3::Matriz3(
    double m00, double m01, double m02,
    double m10, double m11, double m12,
    double m20, double m21, double m22)
{
    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
}

Ponto3D Matriz3::aplicar(const Ponto3D& p) const
{
    double x = m[0][0] * p.getX() + m[0][1] * p.getY() + m[0][2] * p.getZ();
    double y = m[1][0] * p.getX() + m[1][1] * p.getY() + m[1][2] * p.getZ();
    double z = m[2][0] * p.getX() + m[2][1] * p.getY() + m[2][2] * p.getZ();
    return Ponto3D(x, y, z);
}

Matriz3 Matriz3::operator*(const Matriz3& outra) const
{
    Matriz3 r;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            r.m[i][j] = 0.0;
            for (int k = 0; k < 3; ++k)
                r.m[i][j] += m[i][k] * outra.m[k][j];
        }
    }
    return r;
}

Matriz3 Matriz3::identidade()
{
    return Matriz3();
}
