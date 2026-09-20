#include <iostream>
#include<SFML/Graphics.hpp>

using namespace sf;
using namespace std;

RenderWindow janela(VideoMode({ 400,200 }), "Teste:");

bool Gs;
float tami_circ = 100.0f;

void GeraCirc() {

    CircleShape circ(tami_circ);
    circ.setPosition(Vector2f(100.0f, 100.0f));
    circ.setFillColor(Color::Green);

    janela.clear(Color::Blue);

    janela.draw(circ);

    if (Keyboard::isKeyPressed(Keyboard::Key::Space) && tami_circ > 10.0f) {
        tami_circ -= 0.01f;
        circ.setRadius(tami_circ);
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

        if (Gs != false) {
            GeraCirc();
        }

        janela.display();
    }

    return 0;
}

