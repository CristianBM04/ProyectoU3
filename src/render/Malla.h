#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertice {
    glm::vec3 posicion;
    glm::vec3 normal;
    glm::vec2 uv;
};

class Malla {
public:
    Malla(const std::vector<Vertice>& vertices, const std::vector<unsigned>& indices);
    ~Malla();
    Malla(const Malla&) = delete;
    Malla& operator=(const Malla&) = delete;

    void dibujar() const;
    const std::vector<Vertice>& vertices() const { return vertices_; }   // útil luego para ray casting
    const std::vector<unsigned>& indices() const { return indices_; }

private:
    GLuint vao_ = 0, vbo_ = 0, ebo_ = 0;
    std::vector<Vertice> vertices_;
    std::vector<unsigned> indices_;
};