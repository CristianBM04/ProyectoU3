#pragma once
#include "Camara.h"

// WASD mueve, Q/E baja/sube, Shift acelera. Mantener botón derecho para mirar.
class CamaraLibre : public Camara {
public:
    CamaraLibre();
    void actualizar(GLFWwindow* ventana, double dt) override;

private:
    void recalcularFrente();
    float yaw_ = -90.0f;     // -90° = mirando hacia -Z
    float pitch_ = -10.0f;
    float velocidad_ = 4.0f;       // m/s
    float sensibilidad_ = 0.12f;
    bool  mirando_ = false;
    double ultimoX_ = 0, ultimoY_ = 0;
};