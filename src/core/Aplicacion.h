#pragma once
#include <GL/glew.h>      // siempre ANTES de GLFW
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include "render/Shader.h"
#include "camaras/Camara.h"
#include "objetos/Suelo.h"

class Aplicacion {
public:
    Aplicacion(int ancho, int alto, const std::string& titulo);
    ~Aplicacion();
    void ejecutar();

private:
    void iniciarVentana();
    void crearEscena();
    void actualizarSimulacion(double dt);   // paso fijo
    void dibujar(double alpha);

    GLFWwindow* ventana_ = nullptr;
    int ancho_, alto_;
    std::string titulo_;

    std::unique_ptr<Shader> shader_;
    std::unique_ptr<Camara> camara_;
    std::unique_ptr<Suelo>  suelo_;

    static constexpr double SIM_DT = 1.0 / 60.0;
};