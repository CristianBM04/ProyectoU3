#include "Shader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>

GLuint Shader::compilar(GLenum tipo, const std::string& ruta) {
    std::ifstream f(ruta);
    if (!f) throw std::runtime_error("No se encontro el shader: " + ruta + " (ejecuta desde la raiz del proyecto)");
    std::stringstream ss; ss << f.rdbuf();
    std::string src = ss.str();
    const char* c = src.c_str();

    GLuint s = glCreateShader(tipo);
    glShaderSource(s, 1, &c, nullptr);
    glCompileShader(s);

    GLint ok; glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024]; glGetShaderInfoLog(s, 1024, nullptr, log);
        throw std::runtime_error("Error compilando " + ruta + ":\n" + log);
    }
    return s;
}

Shader::Shader(const std::string& rv, const std::string& rf) {
    GLuint v = compilar(GL_VERTEX_SHADER, rv);
    GLuint f = compilar(GL_FRAGMENT_SHADER, rf);
    id_ = glCreateProgram();
    glAttachShader(id_, v); glAttachShader(id_, f);
    glLinkProgram(id_);
    GLint ok; glGetProgramiv(id_, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024]; glGetProgramInfoLog(id_, 1024, nullptr, log);
        throw std::runtime_error(std::string("Error enlazando shader:\n") + log);
    }
    glDeleteShader(v); glDeleteShader(f);
}

Shader::~Shader() { if (id_) glDeleteProgram(id_); }

GLint Shader::ubicacion(const std::string& n) const { return glGetUniformLocation(id_, n.c_str()); }
void Shader::setInt(const std::string& n, int v) const { glUniform1i(ubicacion(n), v); }
void Shader::setBool(const std::string& n, bool v) const { glUniform1i(ubicacion(n), v); }
void Shader::setVec3(const std::string& n, const glm::vec3& v) const { glUniform3fv(ubicacion(n), 1, glm::value_ptr(v)); }
void Shader::setMat4(const std::string& n, const glm::mat4& m) const { glUniformMatrix4fv(ubicacion(n), 1, GL_FALSE, glm::value_ptr(m)); }