#pragma once

#include "Matriz3.hpp"

class Transformacao3D
{
public:
    static Matriz3 escala(double fator);
    static Matriz3 rotacaoX(double anguloGraus);
    static Matriz3 rotacaoY(double anguloGraus);
    static Matriz3 rotacaoZ(double anguloGraus);
};
