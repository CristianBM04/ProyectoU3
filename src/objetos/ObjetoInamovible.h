#pragma once
#include "ObjetoEscena.h"

// Geometría estática: edificio, escaleras, mobiliario, suelo.
// Más adelante entra al BVH y a la malla de navegación una sola vez.
class ObjetoInamovible : public ObjetoEscena {
public:
    using ObjetoEscena::ObjetoEscena;
    void actualizar(double) override {}     // nunca cambia
};