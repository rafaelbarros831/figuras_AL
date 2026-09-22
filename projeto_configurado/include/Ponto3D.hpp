#pragma once

class Ponto3D
{
public:
    Ponto3D(double x = 0.0, double y = 0.0, double z = 0.0);

    double getX() const;
    double getY() const;
    double getZ() const;

    void set(double x, double y, double z);

private:
    double x;
    double y;
    double z;
};
