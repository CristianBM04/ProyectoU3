#include "Camara.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camara::matrizVista() const {
    return glm::lookAt(posicion_, posicion_ + frente_, arriba_);
}

glm::mat4 Camara::matrizProyeccion(float aspecto) const {
    if (ortografica_) {
        float h = tamanoOrto_, w = h * aspecto;
        return glm::ortho(-w, w, -h, h, cerca_, lejos_);
    }
    return glm::perspective(glm::radians(fovGrados_), aspecto, cerca_, lejos_);
}