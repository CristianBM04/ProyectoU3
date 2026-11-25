#version 330 core
in vec3 vPosMundo;
in vec3 vNormal;
in vec2 vUV;

uniform vec3  uColor;
uniform bool  uCuadricula;
uniform vec3  uPosCamara;
uniform vec3  uDirLuz;      //dirección HACIA donde apunta la luz
uniform vec3  uColorLuz;

out vec4 fragColor;

void main() {
    vec3 base = uColor;
    if (uCuadricula) {
        float c = mod(floor(vPosMundo.x) + floor(vPosMundo.z), 2.0);
        base *= mix(0.65, 1.0, c);
    }

    vec3 N = normalize(vNormal);
    vec3 L = normalize(-uDirLuz);
    vec3 V = normalize(uPosCamara - vPosMundo);
    vec3 H = normalize(L + V);                         // Blinn-Phong

    vec3 ambiente = 0.20 * uColorLuz;
    vec3 difusa   = max(dot(N, L), 0.0) * uColorLuz;
    vec3 especular = pow(max(dot(N, H), 0.0), 32.0) * 0.25 * uColorLuz;

    fragColor = vec4((ambiente + difusa) * base + especular, 1.0);
}