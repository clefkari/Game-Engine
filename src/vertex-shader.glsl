#version 450 core

layout(location=0) in vec4 vPosition;
layout(location=1) in vec4 vColor;

out vec4 color;


uniform float uTime;
uniform mat4 uModelViewProjection;

void main() {
    color = vColor*pow(cos(uTime), 2);
    color += (1 - vColor)*(1 - pow(cos(uTime), 2));

    gl_Position = uModelViewProjection * vPosition;
}
