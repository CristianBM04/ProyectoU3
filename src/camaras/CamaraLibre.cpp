#include "CamaraLibre.h"
#include <algorithm>
#include <cmath>

CamaraLibre::CamaraLibre() { recalcularFrente(); }

void CamaraLibre::recalcularFrente() {
    float y = glm::radians(yaw_), p = glm::radians(pitch_);
    frente_ = glm::normalize(glm::vec3(cos(y) * cos(p), sin(p), sin(y) * cos(p)));
}

void CamaraLibre::actualizar(GLFWwindow* w, double dt) {
    // --- mirar con botón derecho ---
    bool presionado = glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
    double x, y; glfwGetCursorPos(w, &x, &y);
    if (presionado && !mirando_) {
        glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        ultimoX_ = x; ultimoY_ = y;
    } else if (!presionado && mirando_) {
        glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    mirando_ = presionado;
    if (mirando_) {
        yaw_   += float(x - ultimoX_) * sensibilidad_;
        pitch_ -= float(y - ultimoY_) * sensibilidad_;
        pitch_ = std::clamp(pitch_, -89.0f, 89.0f);
        ultimoX_ = x; ultimoY_ = y;
        recalcularFrente();
    }

    // --- mover ---
    float v = velocidad_ * float(dt);
    if (glfwGetKey(w, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) v *= 3.0f;
    glm::vec3 derecha = glm::normalize(glm::cross(frente_, arriba_));
    if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) posicion_ += frente_ * v;
    if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS) posicion_ -= frente_ * v;
    if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) posicion_ += derecha * v;
    if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS) posicion_ -= derecha * v;
    if (glfwGetKey(w, GLFW_KEY_E) == GLFW_PRESS) posicion_ += arriba_ * v;
    if (glfwGetKey(w, GLFW_KEY_Q) == GLFW_PRESS) posicion_ -= arriba_ * v;
}