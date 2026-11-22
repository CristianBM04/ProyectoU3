#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

uniform mat4 uModelo;
uniform mat4 uVista;
uniform mat4 uProyeccion;

out vec3 vPosMundo;
out vec3 vNormal;
out vec2 vUV;

void main() {
    vec4 pMundo = uModelo * vec4(aPos, 1.0);          // p_mundo = M * p_local
    vPosMundo = pMundo.xyz;
    vNormal   = mat3(transpose(inverse(uModelo))) * aNormal;
    vUV       = aUV;
    gl_Position = uProyeccion * uVista * pMundo;      // p_clip = P * V * p_mundo
}