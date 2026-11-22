#include "Suelo.h"

std::shared_ptr<Malla> Suelo::crearMalla(float a, float l) {
    float x = a / 2.0f, z = l / 2.0f;
    std::vector<Vertice> v = {
        {{-x, 0, -z}, {0, 1, 0}, {0, 0}},
        {{ x, 0, -z}, {0, 1, 0}, {a, 0}},
        {{ x, 0,  z}, {0, 1, 0}, {a, l}},
        {{-x, 0,  z}, {0, 1, 0}, {0, l}},
    };
    std::vector<unsigned> i = {0, 2, 1, 0, 3, 2};     // CCW visto desde +Y
    return std::make_shared<Malla>(v, i);
}

Suelo::Suelo(float ancho, float largo, glm::vec3 color)
    : ObjetoInamovible("Suelo", crearMalla(ancho, largo), color) {
    cuadricula_ = true;
}