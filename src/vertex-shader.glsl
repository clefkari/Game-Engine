#version 450 core

layout(location=0) in vec4 vPosition;

out vec4 color;

void main() {
    gl_Position = vPosition - vec4(0.5, 0.5, 0.5, 0);
    color = vPosition;
}
