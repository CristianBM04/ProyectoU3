#pragma once
#include "ObjetoInamovible.h"

class Suelo : public ObjetoInamovible {
public:
    Suelo(float ancho, float largo, glm::vec3 color = {0.55f, 0.58f, 0.62f});
private:
    static std::shared_ptr<Malla> crearMalla(float ancho, float largo);
};