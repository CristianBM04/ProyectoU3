#include "Aplicacion.h"
#include "camaras/CamaraLibre.h"
#include <stdexcept>
#include <iostream>

static void alRedimensionar(GLFWwindow*, int w, int h) { glViewport(0, 0, w, h); }

Aplicacion::Aplicacion(int ancho, int alto, const std::string& titulo)
    : ancho_(ancho), alto_(alto), titulo_(titulo) {
    iniciarVentana();
    crearEscena();
}

Aplicacion::~Aplicacion() {
    // Los recursos GL se liberan ANTES de destruir el contexto
    suelo_.reset();
    shader_.reset();
    camara_.reset();
    if (ventana_) glfwDestroyWindow(ventana_);
    glfwTerminate();
}

void Aplicacion::iniciarVentana() {
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
    if (!glfwInit()) throw std::runtime_error("No se pudo iniciar GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    ventana_ = glfwCreateWindow(ancho_, alto_, titulo_.c_str(), nullptr, nullptr);
    if (!ventana_) throw std::runtime_error("No se pudo crear la ventana");

    glfwMakeContextCurrent(ventana_);
    glfwSetFramebufferSizeCallback(ventana_, alRedimensionar);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
        throw std::runtime_error(std::string("No se pudo iniciar GLEW: ") + reinterpret_cast<const char*>(glewGetErrorString(err)));
    glGetError();

    glEnable(GL_DEPTH_TEST);
    std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
}

void Aplicacion::crearEscena() {
    shader_ = std::make_unique<Shader>("Shaders/basicos/phong.vert", "Shaders/basicos/phong.frag");
    camara_ = std::make_unique<CamaraLibre>();       // cámara inicial
    suelo_  = std::make_unique<Suelo>(40.0f, 40.0f); // 40 x 40 m
}

void Aplicacion::ejecutar() {
    double anterior = glfwGetTime();
    double acumulador = 0.0;

    while (!glfwWindowShouldClose(ventana_)) {
        double ahora = glfwGetTime();
        double dtFrame = ahora - anterior;
        anterior = ahora;
        if (dtFrame > 0.25) dtFrame = 0.25;
        acumulador += dtFrame;

        glfwPollEvents();
        if (glfwGetKey(ventana_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(ventana_, GLFW_TRUE);

        camara_->actualizar(ventana_, dtFrame);      // la cámara va a frecuencia de render

        while (acumulador >= SIM_DT) {
            actualizarSimulacion(SIM_DT);
            acumulador -= SIM_DT;
        }

        dibujar(acumulador / SIM_DT);
        glfwSwapBuffers(ventana_);
    }
}

void Aplicacion::actualizarSimulacion(double dt) {
    suelo_->actualizar(dt);
}

void Aplicacion::dibujar(double /*alpha*/) {
    int w, h; glfwGetFramebufferSize(ventana_, &w, &h);
    if (h == 0) return;

    glClearColor(0.53f, 0.70f, 0.88f, 1.0f);         // cielo
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_->usar();
    shader_->setMat4("uVista", camara_->matrizVista());
    shader_->setMat4("uProyeccion", camara_->matrizProyeccion(float(w) / float(h)));
    shader_->setVec3("uPosCamara", camara_->posicion());
    shader_->setVec3("uDirLuz", glm::normalize(glm::vec3(-0.4f, -1.0f, -0.3f)));
    shader_->setVec3("uColorLuz", glm::vec3(1.0f));

    suelo_->dibujar(*shader_);
}