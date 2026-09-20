#include <iostream>
#include<SFML/Graphics.hpp>

using namespace sf;
using namespace std;

RenderWindow janela(VideoMode({600,550}), "Teste:");

bool Gs;
float tami_circ = 100.0f;

float posiY = 100.0f;
float posiX = 100.0f;

void GeraCirc() {

    CircleShape circ(tami_circ);
    circ.setPosition(Vector2f(posiX, posiY));
    circ.setFillColor(Color::Green);

    janela.clear(Color::Blue);

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

int main(){

    while(janela.isOpen() == true){
        while (optional evento = janela.pollEvent()) {

            if (evento ->is<Event::Closed>()) {
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

        janela.display();
    }

    return 0;
}

