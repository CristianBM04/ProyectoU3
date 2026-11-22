#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camara {
public:
    virtual ~Camara() = default;

    virtual void actualizar(GLFWwindow* ventana, double dt) = 0;

    glm::mat4 matrizVista() const;                       // V
    glm::mat4 matrizProyeccion(float aspecto) const;     // P (perspectiva u ortográfica)

    const glm::vec3& posicion() const { return posicion_; }
    void setOrtografica(bool o) { ortografica_ = o; }
    bool esOrtografica() const { return ortografica_; }

protected:
    glm::vec3 posicion_{0.0f, 1.7f, 8.0f};
    glm::vec3 frente_{0.0f, 0.0f, -1.0f};
    glm::vec3 arriba_{0.0f, 1.0f, 0.0f};

    float fovGrados_ = 60.0f;
    float cerca_ = 0.1f;
    float lejos_ = 200.0f;
    bool  ortografica_ = false;
    float tamanoOrto_ = 10.0f;                           // semialto del volumen ortográfico
};