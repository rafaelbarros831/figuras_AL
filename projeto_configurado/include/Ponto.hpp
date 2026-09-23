#pragma once

class Ponto
{
public:
    Ponto(double x, double y);

    double getX() const;
    double getY() const;

private:
    double x;
    double y;
};