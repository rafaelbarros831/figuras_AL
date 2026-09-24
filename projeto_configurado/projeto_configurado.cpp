#include <iostream>
#include<SFML/Graphics.hpp>
#include<vector>

using namespace sf;
using namespace std;

RenderWindow janela(VideoMode({600,550}), "Teste:");

vector <RectangleShape> vLinhas;

int linhas, colunas;

float mediX, mediY;

bool Gs, Ms, Ds, controlquad;
float tami_circ = 100.0f;

float posiY = 100.0f;
float posiX = 100.0f;
float tamquadX = 100.0f;
float tamquadY = 100.0f;
float posiquadX = 100.0f;  
float posiquadY = 100.0f;


void GeraCirc() {

    CircleShape circ(tami_circ);
    circ.setPosition(Vector2f(posiX, posiY));
    circ.setFillColor(Color::Green);

    janela.draw(circ);

    if (Keyboard::isKeyPressed(Keyboard::Key::Space) && tami_circ > 10.0f) {
        tami_circ -= 0.01f;
        circ.setRadius(tami_circ);
    }

    else if (Keyboard::isKeyPressed(Keyboard::Key::S) && tami_circ < 200.0f) {
        tami_circ += 0.01f;
        circ.setRadius(tami_circ);
    }

    else if (Keyboard::isKeyPressed(Keyboard::Key::Up) && posiY > -20.0f) {
        posiY -= 0.1f;
        circ.setPosition(Vector2f(posiX, posiY));
    }

    else if (Keyboard::isKeyPressed(Keyboard::Key::Down) && posiY < 520.0f) {
        posiY += 0.1f;
        circ.setPosition(Vector2f(posiX, posiY));
    }

    else if (Keyboard::isKeyPressed(Keyboard::Key::Left) && posiX > -10.0f) {
        posiX -= 0.1f;
        circ.setPosition(Vector2f(posiX, posiY));
    }

    else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && posiX < 560.0f) {
        posiX += 0.1f;
        circ.setPosition(Vector2f(posiX, posiY));
    }

}

void Geraquad() {
    RectangleShape quad(Vector2f(tamquadX, tamquadY));
    quad.setPosition(Vector2f(posiquadX, posiquadY));
    quad.setFillColor(Color::Red);
    janela.draw(quad);

    if (Keyboard::isKeyPressed(Keyboard::Key::Space) && tamquadX > 10.0f && tamquadY > 10.0f) {
        tamquadX -= 0.01f;
        tamquadY -= 0.01f;
        quad.setSize(Vector2f(tamquadX, tamquadY));
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::S) && tamquadX < 500.0f && tamquadY < 500.0f) {
        tamquadX += 0.01f;
        tamquadY += 0.01f;
        quad.setSize(Vector2f(tamquadX, tamquadY));
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::Q) && tamquadX > 10.0f) {
        tamquadX -= 0.01f;
        quad.setSize(Vector2f(tamquadX, tamquadY));
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::E) && tamquadX < 500.0f) {
        tamquadX += 0.01f;
        quad.setSize(Vector2f(tamquadX, tamquadY));
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::F) && tamquadY > 10.0f) {
        tamquadY -= 0.01f;
        quad.setSize(Vector2f(tamquadX, tamquadY));
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::G) && tamquadY < 500.0f) {
        tamquadY += 0.01f;
        quad.setSize(Vector2f(tamquadX, tamquadY));
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::Up) && posiquadY > -20.0f) {
        posiquadY -= 0.1f;
        quad.setPosition(Vector2f(posiquadX, posiquadY));
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::Down) && posiquadY < 520.0f) {
        posiquadY += 0.1f;
        quad.setPosition(Vector2f(posiquadX, posiquadY));
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::Left) && posiquadX > -10.0f) {
        posiquadX -= 0.1f;
        quad.setPosition(Vector2f(posiquadX, posiquadY));
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && posiquadX < 560.0f) {
        posiquadX += 0.1f;
        quad.setPosition(Vector2f(posiquadX, posiquadY));
    }
}

    void Matriz_ret(int ln, int cn){

        vLinhas.clear();

        mediY = 0.0f;

        for (int i = 0; i < ln; i++) {

            mediX = 10.0f;

            for (int c = 0; c < cn; c++) {
                mediX += 30;
                RectangleShape quadn(Vector2f(20.0f, 20.0f));
                quadn.setFillColor(Color::Green);

                quadn.setPosition(Vector2f(mediX, (10.0f + mediY)));

                vLinhas.push_back(quadn);
                janela.draw(vLinhas.back());
            }
            mediY += 30;
        }
    }


void Quant(){
  cout << "Linhas:";
  cin >> linhas;

  cout << "Colunas:";
  cin >> colunas;
}


int main(){

    Quant();

    while (linhas > 20 || colunas > 20) {
        cout << "O Programa nao aceita valores maiores do que 20.\n";
        Quant();
    }

    while (janela.isOpen() == true) {
        while (optional evento = janela.pollEvent()) {

            if (evento->is<Event::Closed>()) {
                janela.close();
            }
        }

        janela.clear(Color::Blue);

        if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
            Gs = true;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
            Gs = false;
            Ms = false;
            Ds = false;
            controlquad = false;
        }

        if (Gs != false) GeraCirc();

        if (Keyboard::isKeyPressed(Keyboard::Key::Z)) {
            controlquad = true;
        }

          if (controlquad != false) Geraquad();

        if (Keyboard::isKeyPressed(Keyboard::Key::J)) {
			Ms = true;
        }

         if (Ms == true) Matriz_ret(linhas, colunas);

        cout << vLinhas.size()<< endl;

            janela.display();
    }

    return 0;
}

