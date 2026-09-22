#pragma once

#include "Matriz.hpp"

class Transformacao
{
public:
    static Matriz escala(double fator);
    static Matriz reflexaoX();
    static Matriz reflexaoY();
    static Matriz rotacao(double anguloGraus);
};