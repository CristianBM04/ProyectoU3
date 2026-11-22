#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    Shader(const std::string& rutaVert, const std::string& rutaFrag);
    ~Shader();
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void usar() const { glUseProgram(id_); }
    void setInt(const std::string& n, int v) const;
    void setBool(const std::string& n, bool v) const;
    void setVec3(const std::string& n, const glm::vec3& v) const;
    void setMat4(const std::string& n, const glm::mat4& m) const;

private:
    GLuint compilar(GLenum tipo, const std::string& ruta);
    GLint ubicacion(const std::string& n) const;
    GLuint id_ = 0;
};