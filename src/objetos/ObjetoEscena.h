#pragma once
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "render/Malla.h"
#include "render/Shader.h"

struct Transform {
    glm::vec3 posicion{0.0f};
    glm::vec3 rotacionGrados{0.0f};     // Euler XYZ
    glm::vec3 escala{1.0f};

    glm::mat4 matriz() const {          // M = T * R * S
        glm::mat4 m(1.0f);
        m = glm::translate(m, posicion);
        m = glm::rotate(m, glm::radians(rotacionGrados.x), {1, 0, 0});
        m = glm::rotate(m, glm::radians(rotacionGrados.y), {0, 1, 0});
        m = glm::rotate(m, glm::radians(rotacionGrados.z), {0, 0, 1});
        return glm::scale(m, escala);
    }
};

class ObjetoEscena {
public:
    ObjetoEscena(std::string nombre, std::shared_ptr<Malla> malla, glm::vec3 color)
        : nombre_(std::move(nombre)), malla_(std::move(malla)), color_(color) {}
    virtual ~ObjetoEscena() = default;

    virtual void actualizar(double /*dt*/) {}

    virtual void dibujar(const Shader& shader) const {
        shader.setMat4("uModelo", transform.matriz());
        shader.setVec3("uColor", color_);
        shader.setBool("uCuadricula", cuadricula_);
        malla_->dibujar();
    }

    const std::string& nombre() const { return nombre_; }
    Transform transform;

protected:
    std::string nombre_;
    std::shared_ptr<Malla> malla_;
    glm::vec3 color_;
    bool cuadricula_ = false;
};