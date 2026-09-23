#include <iostream>
#include<SFML/Graphics.hpp>
#include<vector>

using namespace sf;
using namespace std;

RenderWindow janela(VideoMode({600,550}), "Teste:");

vector <RectangleShape> vLinhas;

int linhas, colunas;

int mediX = 10;

bool Gs, Ms;
float tami_circ = 100.0f;

float posiY = 100.0f;
float posiX = 100.0f;



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

void Matriz_ret(int ln, int cn) {

    vLinhas.clear();
    
    float mediY = 100;

    for (int i = 0; i < ln; i++) {

        mediX = 10;
        
        for (int c = 0; c < cn; c++) {
            mediX += 30;
            RectangleShape quadn(Vector2f(20.0f, 20.0f));
            quadn.setFillColor(Color::Green);

            quadn.setPosition(Vector2f((100.0f + mediX), mediY));

            vLinhas.push_back(quadn);
            janela.draw(vLinhas.back());
        }
        mediY += 30;
    }
}


int main(){

    cout << "Linhas:";
    cin >> linhas;

    cout << "Colunas:";
    cin >> colunas;

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
        }

        if (Gs != false) {
            GeraCirc();
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::J)) {
			Ms = true;
        }

        if (Ms == true) {
            Matriz_ret(linhas, colunas);
        }

        cout << vLinhas.size()<< endl;

            janela.display();
    }

    return 0;
}

